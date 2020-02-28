/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:53:58 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 20:04:37 by jtaylor          ###   ########.fr       */
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
# define CLEANUP_ERR 0x02
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
	int				to_use_start;
	struct s_rooms	*next;
	struct s_rooms	*prev;
}				t_rooms;

typedef struct	s_link
{
	t_rooms			*room1;
	t_rooms			*room2;
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
	int					handle_first_back_room;
	t_branch			*end_br;
	t_tree				*tree;
}				t_path;

typedef struct	s_path_list
{
	struct s_node		*first;
	struct s_node		*last;
}				t_path_list;

typedef struct	s_all_paths
{
	t_path_list				*path;
	int						path_weight;
	int						ants_to_send;
	int						to_use;
	struct s_all_paths		*next;
}				t_all_paths;

typedef struct	s_split_path
{
	struct s_node	*p1_start_lim;
	struct s_node	*p1_end_lim;
	struct s_node	*p2_start_lim;
	struct s_node	*p2_end_lim;
}				t_split_path;

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
	t_all_paths	*all_paths;
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
void			print_path_list(t_all_paths *path_list);
void			print_all_paths(t_all_paths *path_list);

/*
** Cleanup ---------------------------------------------------------------------
*/

void			free_queue_contents(t_lemin *lemin, struct s_queue *queue);
void			free_lemin_struct(t_lemin *lemin);
void			lemin_free_links(t_lemin *lemin);
void			lemin_free_rooms(t_lemin *lemin);
void			clear_queue(struct s_queue *queue);
void			free_lemin_tree(t_tree *to_free);
void			free_path_struct(t_path *path);
void			free_all_paths(t_lemin *lemin);

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
void			print_ants_endturn(t_lemin *lemin);
t_path_list		*convert_path_to_list(t_lemin *lemin, t_path *path);
void			follow_path_list(t_lemin *lemin);
void			path_list_split_on_shared_nodes(t_lemin *lemin);
void			ants_per_path(t_lemin *lemin);
void			reset_split_path(t_split_path *s);
int				true_if_all_ants_in_exit_room(t_lemin *lemin);
void			ant_arr_init(t_lemin *lemin);
void			populate_path(t_lemin *lemin, t_path *path);
int				check_pointers_in_arr(void **arr, void *target, int lim);
void			populate_path_start_room(t_lemin *lemin, t_path *path);
t_all_paths		*get_all_paths(t_lemin *lemin);
void			get_path_limits(t_path_list *p1, t_path_list *p2,
					t_split_path *s);
struct s_node	*get_first_dup(struct s_node *node_from_other_path,
					t_path_list *path, t_split_path *s, int i);

#endif
