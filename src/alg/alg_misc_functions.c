/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_misc_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:45:53 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 18:46:59 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				ant_arr_init(t_lemin *lemin)
{
	int i;

	i = 0;
	lemin->ant_arr = malloc(sizeof(void *) * (lemin->total_ants + 1));
	lemin->ant_arr[lemin->total_ants] = NULL;
	while (i < lemin->total_ants)
	{
		lemin->ant_arr[i] = lemin->start;
		i++;
	}
}

int					true_if_all_ants_in_exit_room(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] != lemin->end)
			return (0);
		i++;
	}
	return (1);
}
