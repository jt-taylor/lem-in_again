/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_move_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:15:19 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 22:39:39 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
static inline t_branch	*ant_is_in_given_room(t_lemin *lemin, t_branch *root)
{
	int		i;

	i = 0;
	if (!root)
		return (0);
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] == root->content)
			return (root);
		i++;
	}
	return (0);
}

static int				get_index_of_ant_in_room(t_lemin *lemin, t_branch *root)
{
	int		i;

	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] == root->content)
			return (i);
		i++;
	}
	return (-1);
}

static void					check_ant_in_parent_node(t_lemin *lemin, t_branch *root)
{
	int i;

	i = 0;
	if (!root->parent)
		;
	else if (!ant_is_in_given_room(lemin, root) ||
		lemin->end == root->content)
	{
		if (ant_is_in_given_room(lemin, root->parent))
		{
			i = get_index_of_ant_in_room(lemin, root->parent);
			if (i != -1 && !lemin->ant_was_moved[i]++)
				lemin->ant_arr[i] = root->content;
		}
	}
}

static void	move_ants_up_parent_nodes(t_lemin *lemin, t_branch *end)
{
	t_branch		*tmp;

	tmp = end;
	while (tmp->parent != 0)
	{
		check_ant_in_parent_node(lemin, tmp);
		tmp = tmp->parent;
	}
}
*/

int			room_has_ant(t_lemin *lemin, t_branch *branch)
{
	int		i;

	i = 0;
	while (i < lemin->total_ants)
	{
		if (lemin->ant_arr[i] == branch->content)
			return (i);
		i++;
	}
	return (-1);
}

void		move_ants_up_parent_nodes(t_lemin *lemin, t_branch *end)
{
	int				i;
	t_branch		*tmp;

	tmp = end;
	while (tmp->parent)
	{
		i = room_has_ant(lemin, tmp->parent);
		if (i > -1)
		{
			lemin->ant_arr[i] = tmp->content;
			lemin->ant_was_moved[i] = 1;
		}
		tmp = tmp->parent;
	}
}

void		bad_move_ants(t_lemin *lemin, t_branch *end)
{
	ft_bzero(lemin->ant_was_moved, lemin->total_ants * sizeof(int));
	move_ants_up_parent_nodes(lemin, end);
}

