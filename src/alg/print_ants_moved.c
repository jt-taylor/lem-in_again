/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_moved.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:29 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 18:29:15 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				print_ants_endturn(t_lemin *lemin)
{
	int		i;
	int		flag_for_newline;

	flag_for_newline = 0;
	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_was_moved[i])
		{
			ft_printf("L%d-%s ", i + 1,
					(char *)((t_rooms *)lemin->ant_arr[i])->room_name);
			flag_for_newline = 1;
		}
		i++;
	}
	if (flag_for_newline)
		ft_printf("\n");
}

static int			index_of_ant_in_parent_room(t_lemin *lemin,
		struct s_node *node)
{
	int			i;

	i = 0;
	if (!node || !node->next)
		return (-1);
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] == node->next->content)
			return (i);
		i++;
	}
	return (-1);
}

static inline void	follow_path(t_lemin *lemin, t_path_list *path,
		t_all_paths *check)
{
	struct s_node		*tmp;
	int					i;

	tmp = path->first;
	while (tmp)
	{
		i = index_of_ant_in_parent_room(lemin, tmp);
		if (i > -1)
		{
			if ((t_rooms *)tmp->next->content == lemin->start)
			{
				if (check->ants_to_send > 0)
					check->ants_to_send--;
				else
					break ;
			}
			lemin->ant_arr[i] = (t_rooms *)tmp->content;
			lemin->ant_was_moved[i] = 1;
		}
		tmp = tmp->next;
	}
}

void				follow_path_list(t_lemin *lemin)
{
	t_all_paths		*tmp;
	struct s_node	*tmp_node;

	tmp = lemin->all_paths;
	while (tmp && tmp->path)
	{
		tmp_node = tmp->path->first;
		if (tmp->to_use)
			follow_path(lemin, tmp->path, tmp);
		tmp = tmp->next;
	}
}
