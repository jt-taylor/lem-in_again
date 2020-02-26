/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:04:24 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/10 17:35:25 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			parsing_missing_rooms_or_links(t_lemin *lemin)
{
	if (lemin->rooms)
		lemin_free_rooms(lemin);
	if (lemin->links)
		lemin_free_links(lemin);
	ft_dprintf(2, "Error: missing links || rooms\n");
	exit(1);
}

void			parsing_finished_start_is_end(t_lemin *lemin)
{
	lemin_free_rooms(lemin);
	lemin_free_links(lemin);
	ft_dprintf(2, "Error: no start end room\n");
	exit(1);
}

void			parsing_finished_with_no_start_end_room(t_lemin *lemin)
{
	lemin_free_rooms(lemin);
	lemin_free_links(lemin);
	ft_dprintf(2, "Error: no start end room\n");
	exit(1);
}

void			command_comment_followed_by_comment(t_lemin *lemin, char *f1,
		char *f2)
{
	free(f1);
	free(f2);
	if (lemin->rooms)
		lemin_free_rooms(lemin);
	if (lemin->links)
		lemin_free_links(lemin);
	ft_dprintf(2, "Error: Command line followed by comment line\n");
	exit(1);
}

void			link_to_room_does_not_exist(t_lemin *lemin)
{
	lemin_free_rooms(lemin);
	lemin_free_links(lemin);
	ft_dprintf(2, "Error: Link to room does not exist\n");
	exit(1);
}
