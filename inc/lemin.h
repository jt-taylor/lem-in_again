/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:53:58 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 23:41:40 by jtaylor          ###   ########.fr       */
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

# define MALLOC_ERR 0x01
# define PARSING_ERR 0x04

/*
** Structs ---------------------------------------------------------------------
** -----------------------------------------------------------------------------
** -----------------------------------------------------------------------------
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
** parse -----------------------------------------------------------------------
*/

typedef struct	s_rooms
{
	char			*room_name;
	int				room_id;
	int				x;
	int				y;
	char			forward;
	char			backward;
	int				to_use;
	struct s_rooms	*next;
	struct s_rooms	*prev;
	void			*ant_arr;
}				t_rooms;

typedef struct	s_link
{
	t_rooms			*room1;
	t_rooms		*room2;
	struct s_link	*next;
}				t_link;

/*
** path find -------------------------------------------------------------------
*/

typedef struct	s_path
{
	void				**past_rooms;
	t_link				*cur_link;
	t_rooms				*room_to_check;
	struct s_queue		*q;
	int					i;
	int					has_end;
	t_branch			*end_br;
	t_tree				*tree;
}				t_path;

typedef struct	s_lemin
{
	int			total_ants;
	int			room_count;
	int			*ant_was_moved;
	void		**ant_arr;
	t_queue		*queue;
	t_path		*shortest_path;
	t_link		*links;
	t_link		*last_link;
	t_rooms		*start;
	t_rooms		*end;
	t_rooms		*current_room;
	t_rooms		*rooms;
}				t_lemin;

/*
** Prototypes ------------------------------------------------------------------
** -----------------------------------------------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** Parse -----------------------------------------------------------------------
*/

void			parser_main(t_lemin *lemin);
void			parse_comment_rooms(t_lemin *lemin, char *line);
void			add_new_link(t_lemin *lemin, void *room1, void *room2);
void			parse_links(t_lemin *lemin, char *line);
int				get_next_line_wrap(int fd, char **line);
t_rooms			*room_name_checker(t_rooms *rooms, char *room);
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
** debug -----------------------------------------------------------------------
*/

void			print_queue(t_queue *queue);
void			print_tree_contents(t_tree *tree,
					t_branch *specified_branch);

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
int				does_branch_has_link(t_branch *root, void *room1, void *room2);
int				find_endroom_path(t_lemin *lemin, t_branch *root);
int				add_branch(t_branch *root, void *cont, t_branch *new_kid);
void			add_sibbling(t_branch *curr, t_branch *new_sib);
void			add_parent_nodes_to_tree(t_tree *tree);

/*
** alg -------------------------------------------------------------------------
*/

int				alg_main(t_lemin *lemin);
void			update_rooms_with_path_info(t_lemin *lemin, t_path *path);
void			print_ants_endturn(t_lemin *lemin);//rewrite this ?
// right now its in the test_move ants but it should work the way i want to write it
//
/*
** testing
*/

void		bad_move_ants(t_lemin *lemin, t_branch *end);

#endif
