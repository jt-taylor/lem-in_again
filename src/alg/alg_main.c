/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:23:04 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 20:55:55 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Explenation of the alg ::
** so this is edmonds karps but using going by node instead of by link
**
** we find the shortest path -- and disable those start && end link nodes
** we update the nodes from that path to say that 1 ant is moving forward on
** those nodes , and that we can send one ant backwards on them as well ;
**
** then we find the new shortest path ignoring the previously used start/end
** links , including all the others ;
** then we update the nodes from the new path to say that 1 ant is moving forward
** along it and one ant can move back through those nodes , but if a room already
** has an ant moving along it from the previous path we set the ants moving along
** it to 2 and and that 0 ants are allowed to move backwards through those rooms
** then we reapeat untill we can't construct a new path ;
**
** then we need to adjust the paths that share concurrent rooms , and only ever
** 2 paths will share the same room ;
** we also want to save a copy of the shortest path so that with small amounts
** of ants we can check if that is faster sending on one path
** than sending the max flow along concurrent paths ;
** then we calc the # of ants to send on each path ;; not sure exactly how i want
** to do that part yet ;
**
** and then we print the moves on the output ;
*/

static inline int	check_pointers_in_arr(void **arr, void *target, int lim)
{
	int		i;

	i = 0;
	while (i < lim)
	{
		if (target == arr[i])
			return (1);
		i++;
	}
	return (0);
}

static inline void	populate_path_inner1(t_lemin *lemin, t_path *path)
{
	if (!check_pointers_in_arr(path->past_rooms, path->cur_link->room1,
				lemin->room_count))
	{
		enqueue(path->q, path->cur_link->room1);
		path->past_rooms[path->i] = path->cur_link->room1;
		if (!search_branch(path->tree->root, path->cur_link->room1))
			add_branch(path->tree->root, path->room_to_check,
					new_branch(path->cur_link->room1));
		path->i++;
	}
}

static inline void	populate_path_inner2(t_lemin *lemin, t_path *path)
{
	if (!check_pointers_in_arr(path->past_rooms, path->cur_link->room2,
				lemin->room_count))
	{
		enqueue(path->q, path->cur_link->room2);
		path->past_rooms[path->i] = path->cur_link->room2;
		if (!search_branch(path->tree->root, path->cur_link->room2))
			add_branch(path->tree->root, path->room_to_check,
					new_branch(path->cur_link->room2));
		path->i++;
	}
}

// TODO :: add the checking of the avaliablity of the room here
// ie room->forward && room->backward

static inline void	populate_path_start_room(t_lemin *lemin, t_path *path)
{
	path->cur_link = lemin->links;
	path->room_to_check = dequeue(path->q);
	while (path->cur_link)
	{
		if (path->room_to_check == path->cur_link->room1 && path->cur_link->room2->to_use_start == 1)
			populate_path_inner2(lemin, path);
		else if (path->room_to_check == path->cur_link->room2 && path->cur_link->room1->to_use_start == 1)
			populate_path_inner1(lemin, path);
		if (path->room_to_check == lemin->end)
		{
			path->has_end = 1;
			break ;
		}
		path->cur_link = path->cur_link->next;
	}
}

static inline int	populate_path_inner_norm(t_lemin *lemin, t_path *path)
{
	(void)lemin;
	if (path->room_to_check->to_use != 1 && !path->room_to_check->backward)
		return (1);
	if ((path->cur_link->room1 == lemin->end || path->cur_link->room2 == lemin->end) && !path->room_to_check->to_use)
		return (1);
	return (0);
}

int					populate_path(t_lemin *lemin, t_path *path)
{
	while (!queue_isempty(path->q))
	{
		path->cur_link = lemin->links;
		path->room_to_check = dequeue(path->q);
		if (populate_path_inner_norm(lemin, path))
		//if (path->room_to_check->to_use != 1)//(path->room_to_check->forward && !path->room_to_check->backward)
			continue ;
		while (path->cur_link)
		{
			if (path->room_to_check == path->cur_link->room1 && (path->cur_link->room1->to_use || (path->cur_link->room2->to_use != 1 && path->cur_link->room2 != lemin->end) || (path->cur_link->room2->backward == 1 && path->cur_link->room2 != lemin->end)))
				populate_path_inner2(lemin, path);
			else if (path->room_to_check == path->cur_link->room2 && (path->cur_link->room1->to_use || (path->cur_link->room1->to_use != 1 && path->cur_link->room1 != lemin->end) || (path->cur_link->room1->backward == 1 && path->cur_link->room1 != lemin->end)))
				populate_path_inner1(lemin, path);
			if (path->room_to_check == lemin->end)
			{
				path->has_end = 1;
				break ;
			}
			path->cur_link = path->cur_link->next;
		}
	}
	return ((queue_isempty(path->q)) ? 0 : 1);
}

t_path				*init_new_path(t_lemin *lemin)
{
	t_path			*new_path;

	new_path = (t_path *)malloc(sizeof(t_path));
	if (!new_path)
		exit(MALLOC_ERR);
	new_path->past_rooms = (void **)malloc(sizeof(void *) *
			(lemin->room_count + 1));
	ft_bzero(new_path->past_rooms, (sizeof(void *) * (lemin->room_count + 1)));
	new_path->past_rooms[0] = lemin->start;
	new_path->cur_link = 0;
	new_path->i = 1;
	new_path->q = queue_init();
	new_path->tree = gen_tree_init();
	new_path->room_to_check = 0;
	new_path->has_end = 0;
	return (new_path);
}

// TODO :: change the tree to a list and free everthing in the path struct ;
struct s_node		*path_tree_to_list(t_lemin *lemin, t_path *path);

t_path				*get_new_path(t_lemin *lemin)
{
	t_path			*path;

	path = init_new_path(lemin);
	path->tree->root = new_branch(lemin->start);
	enqueue(path->q, lemin->start);
	populate_path_start_room(lemin, path);
	populate_path(lemin, path);
	path->end_br = search_branch(path->tree->root, lemin->end);
	if (path->end_br)
	{
		add_parent_nodes_to_tree(path->tree);
		update_rooms_with_path_info(lemin, path);
	}
	else
	{
		//free the things;
		return (0);
	}
	return (path);
}

void				ant_arr_init(t_lemin *lemin)
{
	int i;

	i = 0;
	lemin->ant_arr = malloc(sizeof(void *) * (lemin->total_ants + 1));
	lemin->ant_arr[lemin->total_ants] = NULL;
	while (i < lemin->total_ants)
	{
		lemin->ant_arr[i] = lemin->start;
		i++;
	}
}

int					true_if_all_ants_in_exit_room(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] != lemin->end)
			return (0);
		i++;
	}
	return (1);
}

/*
**
** void				test_get_second_path(t_lemin *lemin)
** {
** 	t_path		*path;
**
** 	path = get_new_path(lemin);
** 	// wow such great tests
** }
*/

//calculate the total current paths availabe at the moment, ants on the current room

void calculate_ants_foreach_path(t_lemin *lemin /*, current available paths*/)
{
	t_all_paths *tmp;
	struct s_node *tmp_node;
}


void				test_bad_follow_path(t_lemin *lemin)
{
	while (!true_if_all_ants_in_exit_room(lemin))
	{
		//bad_move_ants(lemin, test);

				//bad_move_ants(lemin, test);

		// add a calculator that checks the current ants on the start room, 
		// check the longest path depth - the next_longest path depth based from the ants, 
		// to stop using the current longest path, overtime each long path it will be closed
		// until the shortest path is only available for the current ants
		// if there is only one ant in the room, use the first shortest path founded, for that ant only
		ft_bzero(lemin->ant_was_moved, ((lemin->total_ants) * sizeof(int)));
		follow_path_list(lemin);
		print_ants_endturn(lemin);
		// calculate_paths(lemin);
	}
}

t_all_paths		*init_s_all_paths(void)
{
	t_all_paths			*new;

	new = (t_all_paths *)malloc(sizeof(t_all_paths));
	if (!new)
		exit(MALLOC_ERR);
	new->path = 0;
	new->path_weight = INT_MAX;
	new->ants_to_send = 0;
	new->next = 0;
	return (new);
}

void			add_path_to_all_path_list(t_lemin *lemin, t_all_paths *list, t_path *path)
{
	t_all_paths		*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp->path)
		tmp->path = convert_path_to_list(lemin, path);
	else
	{
		tmp->next = init_s_all_paths();
		tmp->next->path = convert_path_to_list(lemin, path);
	}
	free_path_struct(path);
	path = 0;
}

t_all_paths		*get_all_paths(t_lemin *lemin)
{
	t_all_paths			*list;
	t_path				*tmp;

	list = init_s_all_paths();
	tmp = get_new_path(lemin);
	//for testing while unfinished remove me later
	lemin->shortest_path = tmp;
	if (!tmp)
	{
		ft_dprintf(2, "No path to end room was found\n");
		//free the things
		exit(02);//handle no path to exit
	}
	while (tmp)
	{
		add_path_to_all_path_list(lemin, list, tmp);
		//free tmp
		tmp = get_new_path(lemin);
	}
	//free tmp
	return (list);
}

// TODO :: fix me lol
// simple version for now that only finds one path

int					alg_main(t_lemin *lemin)
{
	//t_path		*path;

	lemin->all_paths = get_all_paths(lemin);
	ant_arr_init(lemin);
	ft_printf("\n");
	// Fix me this is prrof of concept
	path_list_split_on_shared_nodes(lemin);
	test_bad_follow_path(lemin);
	return (1);
}



