/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_populate_edges.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 01:29:57 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/28 01:29:58 by marrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	inner_if_1(t_lemin *lemin, t_path *path)
{
	if (path->room_to_check == path->cur_link->room1 && (
(path->room_to_check->to_use && path->room_to_check->to_use_start) ||
(path->room_to_check->to_use && !path->room_to_check->to_use_start &&
path->cur_link->room2 != lemin->end) ||
(!path->room_to_check->to_use && path->room_to_check->to_use_start &&
path->cur_link->room2 != lemin->start)))
		return (1);
	return (0);
}

int	inner_if_2(t_lemin *lemin, t_path *path)
{
	if (path->room_to_check == path->cur_link->room2 && (
(path->room_to_check->to_use && path->room_to_check->to_use_start) ||
(path->room_to_check->to_use && !path->room_to_check->to_use_start &&
path->cur_link->room1 != lemin->end) ||
(!path->room_to_check->to_use && path->room_to_check->to_use_start &&
path->cur_link->room1 != lemin->start)))
		return (1);
	return (0);
}

int	handle_edge_first_backward_value(t_lemin *lemin,
		t_rooms *rooms, t_path *path)
{
	(void)lemin;
	if (!(path->room_to_check == path->cur_link->room1 ||
		path->room_to_check == path->cur_link->room2))
		return (0);
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
	else if (path->handle_first_back_room)
		path->handle_first_back_room = 0;
	return (1);
}
