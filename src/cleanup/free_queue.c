/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:41:32 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/23 22:50:18 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** assume that the contents var is kept track of outside of this
*/

void		free_queue_contents(t_lemin *lemin, struct s_queue *queue)
{
	(void)lemin;
	while (!queue_isempty(queue))
		dequeue(queue);
	free(queue);
}

void		clear_queue(struct s_queue *queue)
{
	while (!queue_isempty(queue))
		dequeue(queue);
}
