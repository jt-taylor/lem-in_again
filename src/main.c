/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:55:24 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 18:20:36 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static inline void	init_struct(t_lemin *lemin)
{
	lemin->total_ants = 0;
	lemin->room_count = 0;
	lemin->ant_was_moved = 0;
	lemin->ant_arr = 0;
	lemin->links = 0;
	lemin->last_link = 0;
	lemin->start = 0;
	lemin->end = 0;
	lemin->current_room = 0;
	lemin->rooms = 0;
}

int					main(void)
{
	t_lemin		lemin;

	init_struct(&lemin);
	parser_main(&lemin);
	alg_main(&lemin);
	free_lemin_struct(&lemin);
	return (0);
}
