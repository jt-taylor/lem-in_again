/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:23:04 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 01:46:25 by jtaylor          ###   ########.fr       */
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
		if (path->room_to_check == path->cur_link->room1 && path->cur_link->room2->to_use == 1)
			populate_path_inner2(lemin, path);
		else if (path->room_to_check == path->cur_link->room2 && path->cur_link->room1->to_use == 1)
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
	if (path->room_to_check->to_use != 1 && (path->room_to_check != lemin->start))
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
			if (path->room_to_check == path->cur_link->room1 && (path->cur_link->room2->to_use == 1 || (path->cur_link->room2->backward == 1 && path->cur_link->room2 != lemin->end)))
				populate_path_inner2(lemin, path);
			else if (path->room_to_check == path->cur_link->room2 && (path->cur_link->room1->to_use == 1 || (path->cur_link->room1->backward == 1 && path->cur_link->room1 != lemin->end)))
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

void				test_get_second_path(t_lemin *lemin)
{
	t_path		*path;

	path = get_new_path(lemin);
	// wow such great tests
}

void				test_bad_follow_path(t_lemin *lemin)
{
	t_branch		*test;

	test = lemin->shortest_path->end_br;
	//change me
	while (!true_if_all_ants_in_exit_room(lemin))
	{
		bad_move_ants(lemin, test);
		print_ants_endturn(lemin);
	}
}


// TODO :: fix me lol
// simple version for now that only finds one path

int					alg_main(t_lemin *lemin)
{
	t_path		*path;

	path = get_new_path(lemin);
	lemin->shortest_path = path;
	test_get_second_path(lemin);
	if (lemin->shortest_path->has_end)
	{
		ant_arr_init(lemin);
		// Fix me this is prrof of concept
		test_bad_follow_path(lemin);
	}
	else
		ft_dprintf(2, "No path to end room was found\n");//handle no path to end error
	return ((path) ? 1 : 0);
}
