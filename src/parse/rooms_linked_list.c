/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:01:47 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 22:54:51 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms				*room_name_checker(t_rooms *rooms, char *room)
{
	t_rooms *curr;

	curr = rooms;
	if (!room)
		return (0);
	while (curr)
	{
		if (!ft_strcmp(room, curr->room_name))
			return (curr);
		curr = curr->next;
	}
	return (0);
}

static void		init_room(t_rooms *room)
{
	static int		i = 0;

	if (room != 0)
	{
		room->next = 0;
		room->prev = 0;
		room->forward = 0;
		room->backward = 0;
		room->to_use = 1;
		room->room_id = i++;
		room->room_name = 0;
	}
	else
		;
}

t_rooms			*new_room_node(t_rooms *current_room, t_lemin *lemin)
{
	t_rooms		*tmp;

	tmp = (t_rooms *)malloc(sizeof(t_rooms));
	if (!tmp)
		;// handle fail to alloc
	init_room(tmp);
	if (current_room == 0)
	{
		lemin->current_room = tmp;
		lemin->rooms = tmp;
	}
	else
	{
		current_room->next = tmp;
		tmp->prev = current_room;
		lemin->current_room = tmp;
	}
	lemin->room_count += 1;
	return (tmp);
}
