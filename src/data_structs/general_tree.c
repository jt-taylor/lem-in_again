/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:25:28 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/26 23:35:57 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* not sure where this is used
** t_branch	*get_parent(t_branch *root, t_branch *kid)
** {
** 	t_branch *curr;
** 
** 	curr = NULL;
** 	if (root)
** 	{
** 		if (root->kid == kid)
** 		{
** 			curr = root;
** 			return (curr);
** 		}
** 		else
** 		{
** 			if (root->kid && !curr)
** 				curr = (get_parent(root->kid, kid));
** 			if (root->siblings && !curr)
** 				curr = (get_parent(root->siblings, kid));
** 			return (curr);
** 		}
** 	}
** 	return (NULL);
** }
*/

t_tree		*gen_tree_init(void)
{
	t_tree *new_root;

	new_root = malloc(sizeof(t_tree));
	if (!new_root)
		exit(MALLOC_ERR);
	new_root->root = 0;
	return (new_root);
}

t_branch	*new_branch(void *cont)
{
	t_branch	*new_branch;

	new_branch = malloc(sizeof(t_branch));
	new_branch->content = cont;
	new_branch->kid = NULL;
	new_branch->siblings = NULL;
	new_branch->parent = NULL;
	return (new_branch);
}

void		add_sibbling(t_branch *curr, t_branch *new_sib)
{
	t_branch *head;

	head = curr;
	while (curr->siblings)
		curr = curr->siblings;
	if (!curr->siblings)
		curr->siblings = new_sib;
	curr = head;
}

int			add_branch(t_branch *root, void *cont, t_branch *new_kid)
{
	int			i;
	t_branch	*hold;

	i = 0;
	hold = root;
	if (!cont && !new_kid)
		return (0);
	if (!hold)
	{
		hold = new_kid;
		return (1);
	}
	else
	{
		hold = search_branch(hold, cont);
		if (hold)
		{
			if (!hold->kid)
				hold->kid = new_kid;
			else
				add_sibbling(hold->kid, new_kid);
			i = 1;
		}
	}
	return (i);
}
