/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:37:51 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/25 17:37:13 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_new_link(t_lemin *lemin, char *room1, char *room2)
{
	t_link *new_link;
	t_link *head;

	head = lemin->links;
	new_link = malloc(sizeof(t_link));
	new_link->room1 = room1;
	new_link->room2 = room2;
	new_link->to_use = 0;
	new_link->next = NULL;
	if (lemin->end && (ft_strequ(room1, lemin->end->room_name) ||
		ft_strequ(room2, lemin->end->room_name)))
		lemin->end_room_links++;
	if (!lemin->links)
		lemin->links = new_link;
	else
	{
		if (!lemin->last_link)
			lemin->last_link = lemin->links;
		lemin->last_link->next = new_link;
		lemin->last_link = lemin->last_link->next;
		lemin->links = head;
	}
}
