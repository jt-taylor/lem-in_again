/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_moved.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:29 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 21:49:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void					print_ants_endturn(t_lemin *lemin)
{
	int		i;
	int		flag_for_newline;

	flag_for_newline = 0;
	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_was_moved[i])
		{
			ft_printf("L%d-%s ", i + 1, (char *)((t_rooms *)lemin->ant_arr[i])->room_name);
			flag_for_newline = 1;
		}
		i++;
	}
	if (flag_for_newline)
		ft_printf("\n");
}
