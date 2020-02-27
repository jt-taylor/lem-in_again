/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_per_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:36:20 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 14:16:42 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void				get_len_of_path(t_all_paths *path)
{
	int				i;
	struct s_node	*tmp;

	i = 0;
	tmp = path->path->first;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	path->path_weight = i;
	path->ants_to_send = 0;
}

static void				get_len_for_all_paths(t_all_paths *path_list)
{
	t_all_paths			*tmp;

	tmp = path_list;
	while (tmp)
	{
		get_len_of_path(tmp);
		tmp = tmp->next;
	}
}

/*
** the better way to do this is to sort the paths then add ants the first
** path untill the weight is the same as the second then do the same for
** the first && second copmpared to the third the whole way down the path_list
** then after you can just add one to the whole path list for the remaining ants
*/

void				distribute_ants_along_paths(t_lemin *lemin,
		t_all_paths *path_list)
{
	int					i;
	t_all_paths			*tmp;
	t_all_paths			*min;

	i = 0;
	while (i < lemin->total_ants)
	{
		tmp = path_list;
		min = tmp;
		while (tmp)
		{
			if ((min->path_weight + min->ants_to_send) > (tmp->path_weight + tmp->ants_to_send))
				min = tmp;
			tmp = tmp->next;
		}
		min->ants_to_send++;
		i++;
	}
}

void				ants_per_path(t_lemin *lemin)
{
	t_all_paths				*tmp;

	tmp = lemin->all_paths;
	get_len_for_all_paths(tmp);
	distribute_ants_along_paths(lemin, tmp);
}
