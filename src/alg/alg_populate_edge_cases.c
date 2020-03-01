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

/*
** from both inners edge cases, pass only if:
** 1.- the current room to check can be used for go to end and
** used for go to start.
** 2.- the current room to check can be used for go to end but
** can't be used for start, and it's connection is not the end room.
** 3.- the current room to check cannot be used for for go to end,
** but can for start, and it's connection is not the start room.
*/

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

/*
** populate_path_inner_norm edge case---------------------------------
** if the room to check from the current path cannot be used to
** go for the end or for the start skip the populate path,
** also from the link if the link has an end room and the curent
** room to check cannot go to then skip the process too.
** If all the previous checks doesn't pass then keep
** adding nodes to the path
*/

int	populate_path_inner_norm(t_lemin *lemin, t_path *path)
{
	(void)lemin;
	if ((path->room_to_check->to_use != 1 ||
		path->room_to_check->to_use_start != 1)
		&& !path->room_to_check->backward)
		return (1);
	if ((path->cur_link->room1 == lemin->end ||
		path->cur_link->room2 == lemin->end) && !path->room_to_check->to_use)
		return (1);
	return (0);
}
