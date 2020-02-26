/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:37:51 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/25 22:56:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_new_link(t_lemin *lemin, void *room1, void *room2)
{
	t_link *new_link;
	t_link *head;

	head = lemin->links;
	new_link = malloc(sizeof(t_link));
	if (!new_link)
		exit(MALLOC_ERR);
	new_link->room1 = room1;
	new_link->room2 = room2;
	new_link->next = NULL;
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
