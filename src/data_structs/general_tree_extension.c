/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tree_extension.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:19:55 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/25 21:29:28 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			find_endroom_path(t_lemin *lemin, t_branch *root)
{
	if (search_branch(root, lemin->end))
		return (1);
	else
		return (0);
}

/*
** remove this ???
** int			does_branch_has_link(t_branch *root, void *room1, void *room2)
** {
** 	t_branch	*tmp;
** 	char		*root_name;
** 	char		*root_kid_name;
** 	int			i;
** 
** 	i = 0;
** 	root_name = root->content;
** 	root_kid_name = root->kid->content;
** 	if (root && root->kid)
** 	{
** 		if ((ft_strequ(root_name, room1) && ft_strequ(root_kid_name, room2)) ||
** 			(ft_strequ(root_name, room2) && ft_strequ(root_kid_name, room1)))
** 			return (1);
** 		else
** 		{
** 			tmp = root;
** 			while (tmp && !i)
** 			{
** 				if (tmp->kid)
** 					i = does_branch_has_link(tmp->kid, room1, room2);
** 				tmp = tmp->siblings;
** 			}
** 		}
** 	}
** 	return (i);
** }
*/

t_branch	*search_branch(t_branch *root, void *cont)
{
	t_branch *curr;

	curr = NULL;
	if (root)
	{
		if (root->content == cont)
		{
			curr = root;
			return (curr);
		}
		else
		{
			if (root->kid && !curr)
				curr = (search_branch(root->kid, cont));
			if (root->siblings && !curr)
				curr = (search_branch(root->siblings, cont));
			return (curr);
		}
	}
	return (NULL);
}
