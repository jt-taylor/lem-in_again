/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_erorrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 09:19:43 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/10 16:00:25 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		invalid_ants_error(t_lemin *lemin)
{
	(void)lemin;
	ft_dprintf(2, "0 ants to send\n");
	exit(PARSING_ERR);
}

void		failed_read_line_err(t_lemin *lemin)
{
	(void)lemin;
	ft_dprintf(2, "Error reading input line");
	exit(PARSING_ERR);
}

void		failed_read_room(t_lemin *lemin, char *input_line)
{
	t_rooms		*tmp;

	free(input_line);
	while (lemin->rooms != 0)
	{
		tmp = lemin->rooms;
		lemin->rooms = lemin->rooms->next;
		free(tmp->room_name);
		free(tmp);
	}
	ft_dprintf(2, "failed read room\n");
	exit(PARSING_ERR);
}

void		failed_read_start_end_room(t_lemin *lemin, char *line, char *in)
{
	free(line);
	failed_read_room(lemin, in);
}
