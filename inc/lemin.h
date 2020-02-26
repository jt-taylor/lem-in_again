/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:53:58 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 17:59:04 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

/*
** Includes && Macros ----------------------------------------------------------
*/

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define PARSING_ERR 0x04

/*
** Structs ---------------------------------------------------------------------
*/

/*
** queue -----------------------------------------------------------------------
*/

struct			s_node
{
	void			*content;
	struct s_node	*next;
};

typedef struct	s_queue
{
	struct s_node		*first;
	struct s_node		*last;
}				t_queue;

/*
** general tree ----------------------------------------------------------------
*/

typedef struct	s_branch
{
	void			*content;
	struct s_branch	*siblings;
	struct s_branch	*kid;
	struct s_branch	*parent;
}				t_branch;

typedef struct	s_tree
{
	struct s_branch *root;
}				t_tree;

/*
** lemin structs ---------------------------------------------------------------
*/

typedef struct	s_rooms
{
	char			*room_name;
	int				room_id;
	int				x;
	int				y;
	char			forward;
	char			backward;
	int				links_counter;
	struct s_rooms	*next;
	struct s_rooms	*prev;
	void			*ant_arr;
}				t_rooms;

typedef struct	s_link
{
	char			*room1;
	char			*room2;
	int				to_use;
	struct s_link	*next;
}				t_link;

typedef struct	s_lemin
{
	int			total_ants;
	int			room_count;
	int			end_room_links;
	int			*ant_was_moved;
	char		**ant_arr;
	t_queue		*queue;
	t_link		*links;
	t_link		*last_link;
	t_rooms		*start;
	t_rooms		*end;
	t_rooms		*current_room;
	t_rooms		*rooms;
}				t_lemin;

/*
** Prototypes ------------------------------------------------------------------
*/

/*
** Parse -----------------------------------------------------------------------
*/

void			parser_main(t_lemin *lemin);
void			parse_comment_rooms(t_lemin *lemin, char *line);
void			add_new_link(t_lemin *lemin, char *room1, char *room2);
void			parse_links(t_lemin *lemin, char *line);
int				get_next_line_wrap(int fd, char **line);
int				room_name_checker(t_rooms *rooms, char *room);
t_rooms			*new_room_node(t_rooms *current_room, t_lemin *lemin);

/*
** Erorrs ----------------------------------------------------------------------
*/

void			command_comment_followed_by_comment(t_lemin *lemin, char *f1,
					char *f2);
void			parsing_finished_with_no_start_end_room(t_lemin *lemin);
void			link_to_room_does_not_exist(t_lemin *lemin);
void			parsing_missing_rooms_or_links(t_lemin *lemin);
void			parsing_finished_start_is_end(t_lemin *lemin);
void			failed_read_room(t_lemin *lemin, char *input_line);
void			failed_read_line_err(t_lemin *lemin);
void			invalid_ants_error(t_lemin *lemin);
void			failed_read_start_end_room(t_lemin *lemin,
						char *line, char *in);

/*
** Cleanup ---------------------------------------------------------------------
*/

void			free_queue_contents(t_lemin *lemin, struct s_queue *queue);
void			free_lemin_struct(t_lemin *lemin);
void			lemin_free_links(t_lemin *lemin);
void			lemin_free_rooms(t_lemin *lemin);
void			clear_queue(struct s_queue *queue);

/*
** Queue -----------------------------------------------------------------------
*/

struct s_queue	*queue_init(void);
void			enqueue(struct s_queue *queue, void *content);
void			*dequeue(struct s_queue *queue);
void			*queue_peek(struct s_queue *queue);
int				queue_isempty(struct s_queue *queue);

/*
** General tree ----------------------------------------------------------------
*/

t_tree			*gen_tree_init(void);
t_branch		*new_branch(void *cont);
t_branch		*search_branch(t_branch *root, void *cont);
t_branch		*search_branch_str(t_branch *root, char *cont);
int				does_branch_has_link(t_branch *root, void *room1, void *room2);
int				find_endroom_path(t_lemin *lemin, t_branch *root);
int				add_branch(t_branch *root, void *cont, t_branch *new_kid);
void			add_sibbling(t_branch *curr, t_branch *new_sib);
void			add_parent_nodes_to_tree(t_tree *tree_root);

#endif
