/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_parent_nodes_to_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:50:03 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/05 12:56:53 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static inline void	tree_search_and_add_parent(t_branch *root, t_branch *parent)
{
	struct s_branch	*tmp;

	if (!root)
		return ;
	root->parent = parent;
	tmp = root;
	while (tmp)
	{
		tmp->parent = parent;
		tree_search_and_add_parent(tmp->kid, tmp);
		tmp = tmp->siblings;
	}
}

void				add_parent_nodes_to_tree(t_tree *tree)
{
	tree->root->parent = NULL;
	tree_search_and_add_parent(tree->root, 0);
}
