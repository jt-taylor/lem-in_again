/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_paths_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:09:24 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 21:20:40 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		free_path(t_path_list *path)
{
	struct s_node		*tmp;

	while (path->first)
	{
		tmp = path->first;
		path->first = path->first->next;
		free(tmp);
	}
	free(path);
}

void			free_all_paths(t_lemin *lemin)
{
	t_all_paths	*tmp;

	while (lemin->all_paths)
	{
		tmp = lemin->all_paths;
		lemin->all_paths = lemin->all_paths->next;
		free_path(tmp->path);
		free(tmp);
	}
}
