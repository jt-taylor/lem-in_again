/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path_list_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:59:15 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 15:31:28 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_path_list(t_all_paths *path_list)
{
	t_all_paths		*tmp;

	tmp = path_list;
	while (tmp)
	{
		if (tmp->to_use)
			ft_printf("\n%s::\nWeight = %d\nto_Send = %d\nAGG = %d\n",
				((t_rooms *)tmp->path->first->next->content)->room_name,
				tmp->path_weight, tmp->ants_to_send, (tmp->path_weight +
					tmp->ants_to_send));
		tmp = tmp->next;
	}
}
