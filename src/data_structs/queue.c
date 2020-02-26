/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:43:09 by jtaylor           #+#    #+#             */
/*   Updated: 2020/01/26 16:43:10 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

struct s_queue	*queue_init(void)
{
	struct s_queue		*new;

	new = malloc(sizeof(struct s_queue));
	new->first = 0;
	new->last = 0;
	return (new);
}

void			enqueue(struct s_queue *queue, void *content)
{
	struct s_node *tmp;

	tmp = malloc(sizeof(struct s_node));
	tmp->content = content;
	tmp->next = 0;
	if (!queue->first)
		queue->first = tmp;
	if (queue->last)
		queue->last->next = tmp;
	queue->last = tmp;
}

void			*dequeue(struct s_queue *queue)
{
	struct s_node	*tmp;
	void			*content;

	if (queue == 0 || queue->first == 0)
		return (0);
	tmp = queue->first;
	content = tmp->content;
	queue->first = queue->first->next;
	if (queue->first == 0)
		queue->last = 0;
	free(tmp);
	return (content);
}

void			*queue_peek(struct s_queue *queue)
{
	void		*c;

	if (queue == 0 || queue->first == 0)
		return (0);
	c = queue->first->content;
	return (c);
}

int				queue_isempty(struct s_queue *queue)
{
	if (queue == 0 || queue->first == 0)
		return (1);
	return (0);
}
