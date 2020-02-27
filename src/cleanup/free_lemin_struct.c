/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lemin_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:38:02 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 21:22:40 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** the strings in lemin->ant_arr are free'd elsewhere
*/

static void		lemin_free_ant(t_lemin *lemin)
{
	free(lemin->ant_was_moved);
	free(lemin->ant_arr);
}

void			lemin_free_rooms(t_lemin *lemin)
{
	t_rooms	*tmp;

	tmp = lemin->rooms;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->prev != 0)
	{
		tmp = tmp->prev;
		free(tmp->next->room_name);
		free(tmp->next);
	}
	free(tmp->room_name);
	free(tmp);
	lemin->rooms = 0;
	lemin->start = 0;
	lemin->end = 0;
	lemin->current_room = 0;
}

/*
static void		lemin_free_path(t_lemin *lemin)
{
	free(lemin->current_best_group->paths_in_list);
	free(lemin->paths);
	lemin->paths = 0;
}
*/

void			lemin_free_links(t_lemin *lemin)
{
	struct s_link	*tmp;
	struct s_link	*to_del;

	tmp = lemin->links;
	while (tmp)
	{
		to_del = tmp;
//		free(tmp->room1);
//		free(tmp->room2);
		tmp = tmp->next;
		free(to_del);
	}
	lemin->links = 0;
	lemin->last_link = 0;
}

/*
** free the whole lemin struct -------------------------------------------------
*/

void			free_lemin_struct(t_lemin *lemin)
{
	lemin_free_ant(lemin);
	lemin_free_rooms(lemin);
	lemin_free_links(lemin);
	free_all_paths(lemin);
	lemin->ant_arr = 0;
}
