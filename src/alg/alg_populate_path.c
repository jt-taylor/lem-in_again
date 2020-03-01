/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_populate_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:52:27 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/28 00:05:47 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** populate_path_inner---------------------------------
** it adds a new room to the tree, based from the current room
** and the current link, if the room has not been added before
** to the current path search and it's not in the tree,
** add the room to the tree, else don't add the node. The path index
** will still incrementing if the room hasn't been checked before.
*/

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

/*
** populate_path_start_room---------------------------------
** It populates the tree with all the nodes connected from
** the room_to_check room, and if the room_to_check is the endroom,
** break right away after setting the node and set the path
** has an end room.
*/

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

/*
** populate_path--------------------------------------------
** the populate_path will keep adding nodes to the tree based
** from the edge cases, until an endroom has found and the current
** path has an endroom set from populate_path_start_room,
** if not keep adding nodes until queue is empty.
*/

void				populate_path(t_lemin *lemin, t_path *path)
{
	while (!queue_isempty(path->q))
	{
		path->cur_link = lemin->links;
		path->room_to_check = dequeue(path->q);
		if (populate_path_inner_norm(lemin, path))
			continue ;
		while (path->cur_link)
		{
			if (inner_if_1(lemin, path))
				populate_path_inner2(lemin, path);
			else if (inner_if_2(lemin, path))
				populate_path_inner1(lemin, path);
			if (path->room_to_check == lemin->end && (path->has_end = 1))
				break ;
			path->cur_link = path->cur_link->next;
		}
	}
}
