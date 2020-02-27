/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_contents.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:17:59 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 23:36:46 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static inline void	print_branch_children(t_branch *root)
{
	t_branch	*tmp;

	tmp = root;
	ft_dprintf(2, "\tBP:%p\tContent::%s\n", root,
			(char *)((t_rooms *)root->content)->room_name);
	tmp = tmp->siblings;
	while (tmp)
	{
		ft_dprintf(2, "\t\tSIB:%p\tContent::%s\n", tmp,
				(char *)((t_rooms *)tmp->content)->room_name);
		tmp = tmp->siblings;
	}
}

static inline void	print_branch_parents(t_branch *root)
{
	t_branch	*tmp;

	tmp = root;
	ft_dprintf(2, "\tBP:%p\tParent::\"%s\"\n", root, (root->parent) ?
			(char *)((t_rooms *)root->parent->content)->room_name : "NULL");
	tmp = tmp->siblings;
	while (tmp)
	{
		ft_dprintf(2, "\t\tSIB:%p\tParent::\"%s\"\n", tmp, (tmp->parent) ?
				(char *)((t_rooms *)tmp->parent->content)->room_name : "NULL");
		tmp = tmp->siblings;
	}
}

static inline void	find_nodes_at_depth(t_branch *root, int depth,
		int cur_depth, int mode)
{
	struct s_branch	*tmp;

	if (!root || cur_depth > depth)
		return ;
	if (cur_depth == depth)
	{
		if (mode == 0)
			print_branch_children(root);
		if (mode == 1)
			print_branch_parents(root);
	}
	else
	{
		tmp = root;
		while (tmp)
		{
			find_nodes_at_depth(tmp->kid, depth, cur_depth + 1, mode);
			tmp = tmp->siblings;
		}
	}
}

void				print_tree_node_parents(t_tree *tree,
		t_branch *specified_branch)
{
	int		i;

	i = 0;
	ft_dprintf(2, "Tree Printout ::\t%p\nLayers 0 - 10\n", tree);
	while (i < 10)
	{
		ft_dprintf(2, "At depth %i\n", i);
		find_nodes_at_depth(specified_branch, i, 0, 1);
		i++;
	}
}

void				print_tree_contents(t_tree *tree,
		t_branch *specified_branch)
{
	int		i;

	i = 0;
	ft_dprintf(2, "Tree Printout ::\t%p\nLayers 0 - 10\n", tree);
	while (i < 10)
	{
		ft_dprintf(2, "At depth %i\n", i);
		find_nodes_at_depth(specified_branch, i, 0, 0);
		i++;
	}
}
