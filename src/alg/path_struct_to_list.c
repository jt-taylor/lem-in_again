/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:37:58 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 03:04:35 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path_list			*init_path_list(void)
{
	t_path_list			*new;

	new = (t_path_list *)malloc(sizeof(t_path_list));
	if (!new)
		exit(MALLOC_ERR);
	new->first = 0;
	new->last = 0;
	return (new);
}

static void					add_to_list(t_path_list *path, t_rooms *content)
{
	struct s_node		*item;

	item = (struct s_node *)malloc(sizeof(struct s_node));
	if (!item)
		exit(MALLOC_ERR);
	item->content = content;
	item->next = 0;
	if (path->first == 0)
	{
		path->first = item;
		path->last = item;
	}
	else
	{
		path->last->next = item;
		path->last = item;
	}
}

t_path_list					*convert_path_to_list(t_lemin *lemin, t_path *path)
{
	(void)lemin;
	t_path_list		*l;
	t_branch		*tmp;

	l = init_path_list();
	if (!path->end_br)
	{
		free(l);
		return (0);
	}
	tmp = path->end_br;
	while (tmp)
	{
		add_to_list(l, (t_rooms *)tmp->content);
		tmp = tmp->parent;
	}
	return (l);
}
