/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:10:52 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/10 17:36:47 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** this is mostly a carbon copy of the parse_rooms function in parsing_main.c
** but it sets lemin->start to the parsed room at the end
*/

static t_rooms		*parse_start_room(t_lemin *lemin, char *line, char *in_line)
{
	int			i;
	t_rooms		*room;

	room = new_room_node(lemin->current_room, lemin);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	room->room_name = ft_strndup(line, i);
	if (line[i] && i++ && line[i])
		room->x = ft_atoi(line + i);
	else
		failed_read_start_end_room(lemin, line, in_line);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && i++ && line[i])
		room->y = ft_atoi(line + i);
	else
		failed_read_start_end_room(lemin, line, in_line);
	lemin->start = room;
	return (room);
}

/*
** the same as the above function but for lemin->end
*/

static t_rooms		*parse_end_room(t_lemin *lemin, char *line, char *in_line)
{
	int			i;
	t_rooms		*room;

	room = new_room_node(lemin->current_room, lemin);
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	room->room_name = ft_strndup(line, i);
	if (line[i] && i++ && line[i])
		room->x = ft_atoi(line + i);
	else
		failed_read_start_end_room(lemin, line, in_line);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] && i++ && line[i])
		room->y = ft_atoi(line + i);
	else
		failed_read_start_end_room(lemin, line, in_line);
	lemin->end = room;
	return (room);
}

/*
** ignore unknown commands
*/

void				parse_comment_rooms(t_lemin *lemin, char *line)
{
	char		*tmp;

	if (get_next_line_wrap(0, &tmp) > 0)
	{
		if (tmp[0] == '#')
			command_comment_followed_by_comment(lemin, line, tmp);
		if (ft_strstr(line, "start"))
			parse_start_room(lemin, tmp, line);
		else if (ft_strstr(line, "end"))
			parse_end_room(lemin, tmp, line);
		else
			;
		free(tmp);
	}
	else
	{
		free(line);
		ft_dprintf(2, "Missing line after ##line");
		exit(PARSING_ERR);
	}
}
