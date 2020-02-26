/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:13:36 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 23:37:11 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_queue(t_queue *queue)
{
	struct s_node	*tmp;

	ft_printf("queue is[");
	tmp = queue->first;
	if (!tmp)
	{
		ft_printf("NULL]\n ");
		return ;
	}
	while (tmp)
	{
		ft_printf("%s, ", (char *)((t_rooms *)tmp->content)->room_name);
		tmp = tmp->next;
	}
	ft_printf("]");
}
