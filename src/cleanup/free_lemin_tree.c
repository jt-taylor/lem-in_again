/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lemin_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:47:45 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 20:40:20 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			tree_free_branch_recur(t_branch *root)
{
	struct s_branch	*tmp;
	struct s_branch	*to_del;

	if (!root)
		return ;
	tmp = root;
	while (tmp)
	{
		tree_free_branch_recur(tmp->kid);
		to_del = tmp;
		tmp = tmp->siblings;
		free(to_del);
	}
}

void			free_lemin_tree(t_tree *tree)
{
	tree_free_branch_recur(tree->root);
	free(tree);
	tree = 0;
}
