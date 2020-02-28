/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_populate_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:52:27 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 21:17:13 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

void				populate_path_start_room(t_lemin *lemin, t_path *path)
{
	path->cur_link = lemin->links;
	path->room_to_check = dequeue(path->q);
	while (path->cur_link)
	{
		if (path->room_to_check == path->cur_link->room1 &&
				path->cur_link->room2->to_use_start == 1)
			populate_path_inner2(lemin, path);
		else if (path->room_to_check == path->cur_link->room2 &&
				path->cur_link->room1->to_use_start == 1)
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
	if ((path->room_to_check->to_use != 1 || path->room_to_check->to_use_start != 1) && !path->room_to_check->backward)
		return (1);
//	if ((path->cur_link->room1 == lemin->start || path->cur_link->room2 == lemin->start) && !path->room_to_check->to_use_start)
//		return (0);
	if ((path->cur_link->room1 == lemin->end ||
		path->cur_link->room2 == lemin->end) && !path->room_to_check->to_use)
		return (1);
	return (0);
}

int			handle_edge_first_backward_value(t_lemin *lemin,
		t_rooms *rooms, t_path *path)
{
	(void)lemin;
	if (path->handle_first_back_room == 1)
	{
		if (path->cur_link->room1->backward && path->cur_link->room2->backward)
		{
			path->handle_first_back_room++;
			return (1);
		}
		else
			return (0);
	}
	if (rooms->backward)
		path->handle_first_back_room += 1;
	else
		path->handle_first_back_room = 0;
	return (1);
}

void				populate_path(t_lemin *lemin, t_path *path)
{
	while (!queue_isempty(path->q))
	{
		path->cur_link = lemin->links;
		path->room_to_check = dequeue(path->q);
		if (populate_path_inner_norm(lemin, path))
			continue ;
		while (path->cur_link)// && handle_edge_first_backward_value(lemin, path->room_to_check, path))
		{
			if (path->room_to_check == path->cur_link->room1 &&
((path->cur_link->room1->to_use && (path->cur_link->room1->to_use_start && path->cur_link->room2 != lemin->start)) || (path->cur_link->room2->to_use != 1 &&
path->cur_link->room2 != lemin->end) || (path->cur_link->room2->backward == 1
	&& path->cur_link->room2 != lemin->end)))
				populate_path_inner2(lemin, path);
			else if (path->room_to_check == path->cur_link->room2 &&
((path->cur_link->room1->to_use && (path->cur_link->room2->to_use_start && path->cur_link->room1 != lemin->start)) || (path->cur_link->room1->to_use != 1 &&
path->cur_link->room1 != lemin->end) || (path->cur_link->room1->backward == 1 &&
path->cur_link->room1 != lemin->end)))
				populate_path_inner1(lemin, path);
			if (path->room_to_check == lemin->end && (path->has_end = 1))
				break ;
			path->cur_link = path->cur_link->next;
		}
	}
}
