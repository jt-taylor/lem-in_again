/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_list_split_on_shared_nodes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:47:37 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 22:29:22 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/* the caveat of doing it this way is that we need to free the nodes inbetween
** the two limits
** but other than that this should be okay
*/

struct s_node	*find_node_in_path(struct s_node *node, t_path_list *path)
{
	struct s_node		*tmp;

	tmp = path->first->next;
	while (tmp)
	{
		if (tmp->content == node->content)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

struct s_node	*get_first_dup(struct s_node *node_from_other_path,
		t_path_list *path, t_split_path *s, int i)
{
	struct s_node		*tmp;
	struct s_node		*tmp2;

	tmp = node_from_other_path;
	while (tmp)
	{
		tmp2 = find_node_in_path(tmp, path);
		if (tmp2)
			break ;
		tmp = tmp->next;
	}
	if (i)
	{
		s->p1_start_lim = tmp;
		s->p2_end_lim = tmp2;
	}
	else
	{
		s->p2_start_lim = tmp;
		s->p1_end_lim = tmp2;
	}
	return (0);
}

void			free_inbetween_nodes_in_swap(t_split_path *s)
{
	struct s_node		*tmp;
	struct s_node		*to_free;

	tmp = s->p1_start_lim;
	while (tmp)
	{
		if (tmp == s->p1_end_lim)
			break ;
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
	tmp = s->p2_start_lim;	while (tmp)
	{
		if (tmp == s->p2_end_lim)
			break ;
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
	}
}

static void		swap_nodes(t_split_path *s, t_path_list *p1, t_path_list *p2)
{
	struct s_node		*tmp;

	tmp = p1->first;
	while (tmp && tmp->next != s->p1_start_lim)
		tmp = tmp->next;
	tmp->next = s->p2_end_lim;
	tmp = p2->first;
	while (tmp && tmp->next != s->p2_start_lim)
		tmp = tmp->next;
	tmp->next = s->p1_end_lim;
	free_inbetween_nodes_in_swap(s);
}

void			get_path_limits(t_path_list *p1, t_path_list *p2,
		t_split_path *s)
{
	//i don't thinkthis will ever run on a path of just start->end
	get_first_dup(p1->first->next, p2, s, 1);
	get_first_dup(p2->first->next, p1, s, 0);
}

void			reset_split_path(t_split_path *s)
{
	s->p1_start_lim = 0;
	s->p1_end_lim = 0;
	s->p2_start_lim = 0;
	s->p2_end_lim = 0;
}

void			path_list_split_on_shared_nodes(t_lemin *lemin)
{
	t_all_paths		*p1;
	t_all_paths		*p2;
	t_split_path	s;

	p1 = lemin->all_paths;
	while (p1)
	{
		p2 = lemin->all_paths->next;
		while (p2)
		{
			reset_split_path(&s);
			get_path_limits(p1->path, p2->path, &s);
			swap_nodes(&s, p1->path, p2->path);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}
