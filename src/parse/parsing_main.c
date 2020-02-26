/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:29:42 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 22:21:35 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** kind of hard to fill this in without knowing how we want to store the rooms
** and the links
*/

static void		parse_ant_count(t_lemin *lemin)
{
	char	*line;

	if (get_next_line_wrap(0, &line) > 0 && ft_strlen(line) <= 10)
		lemin->total_ants = ft_atoi(line);
	else
	{
		free(line);
		failed_read_line_err(lemin);
	}
	free(line);
	if (lemin->total_ants <= 0 || lemin->total_ants >= INT_MAX)
		invalid_ants_error(lemin);
	lemin->ant_was_moved = malloc((lemin->total_ants) * sizeof(int));
	if (!lemin->ant_was_moved)
		exit(MALLOC_ERR);
}

static void		parse_rooms(t_lemin *lemin, char *line)
{
	int			i;
	t_rooms		*room;

	room = new_room_node(lemin->current_room, lemin);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	room->room_name = ft_strndup(line, i);
	if (line[i] && i++)
		room->x = ft_atoi(line + i);
	else
		failed_read_room(lemin, line);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && i++)
		room->y = ft_atoi(line + i);
	else
		failed_read_room(lemin, line);
}

/*
**		//this is assuming that the '-' char is never used in the name of the
**		//rooms , this can be simplified if we assume that the rooms finish
**		//being declared before the links are added , ie we add all the rooms
**		//then the links -- but im not sure if the format is always rooms
**		//then links
*/

static void		parse_inner(t_lemin *lemin)
{
	char	*line;

	while (get_next_line_wrap(0, &line) > 0)
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				ft_printf("setting new room\n");
				parse_comment_rooms(lemin, line);
			}
			else
				;
		}
		else if (ft_strchr(line, '-'))
			parse_links(lemin, line);
		else
			parse_rooms(lemin, line);
		free(line);
	}
	free(line);
}

void			parser_main(t_lemin *lemin)
{
	parse_ant_count(lemin);
	parse_inner(lemin);
	if (!lemin->rooms || !lemin->links)
		parsing_missing_rooms_or_links(lemin);
	if (!lemin->end || !lemin->start)
		parsing_finished_with_no_start_end_room(lemin);
	if (lemin->start == lemin->end)
		parsing_finished_start_is_end(lemin);
}
