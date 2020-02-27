/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants_moved.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:49:29 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 16:33:26 by jtaylor          ###   ########.fr       */
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

static int					index_of_ant_in_parent_room(t_lemin *lemin, struct s_node *node)
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

static inline void	follow_path(t_lemin *lemin, t_path_list *path)
{
	struct s_node		*tmp;
	int					i;

	tmp = path->first;
	while (tmp)
	{
		i = index_of_ant_in_parent_room(lemin, tmp);
		if (i > -1)
		{
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
	//int				i;

	tmp = lemin->all_paths;
	// for testing that it actually follows the path in the ll ; 
	// need to write the functionality to split the path on the concurrent nodes
	//follow_path(lemin, lemin->all_paths->path);
	//
	while (tmp && tmp->path)
	{
		tmp_node = tmp->path->first;
//		if (tmp->ants_to_send)
//			;
		follow_path(lemin, tmp->path);
		//not sure where i want to do the ant calculate
		tmp = tmp->next;
	}
}
