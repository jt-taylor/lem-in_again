/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 23:03:07 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 23:09:38 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			debugger_print_path(t_all_paths *a, t_all_paths *b)
{
	struct s_node		*tmp;
	struct s_node		*tmp1;

	ft_printf("Duplicate nodes between paths a && b\n\n");
	tmp = a->path->first;
	while (tmp)
	{
		tmp1 = b->path->first;
		while (tmp1)
		{
			if (tmp1->content == tmp->content)
			{
				ft_printf("Duplicate node :\t%s\n",
					((t_rooms *)tmp->content)->room_name);
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}
