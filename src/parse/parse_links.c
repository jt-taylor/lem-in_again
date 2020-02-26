/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:21:32 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/10 17:13:57 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** for norme
*/

static inline void	parse_link_inner(t_lemin *lemin, char **rooms)
{
	char	*tmp;

	while (get_next_line_wrap(0, &tmp) > 0)
	{
		if (tmp[0] == '#')
			;
		else
		{
			rooms = ft_strsplit(tmp, '-');
			if (room_name_checker(lemin->rooms, rooms[0]) &&
				room_name_checker(lemin->rooms, rooms[1]))
				add_new_link(lemin, rooms[0], rooms[1]);
			else
				link_to_room_does_not_exist(lemin);
			free(rooms);
		}
		free(tmp);
	}
	free(tmp);
}

void				parse_links(t_lemin *lemin, char *line)
{
	char	**rooms;

	rooms = ft_strsplit(line, '-');
	if (room_name_checker(lemin->rooms, rooms[0]) &&
		room_name_checker(lemin->rooms, rooms[1]))
		add_new_link(lemin, rooms[0], rooms[1]);
	else
		exit(0);
	free(rooms);
	parse_link_inner(lemin, rooms);
}
