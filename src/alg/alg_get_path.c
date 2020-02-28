/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:47:31 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 23:44:17 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_all_paths		*init_s_all_paths(void)
{
	t_all_paths			*new;

	new = (t_all_paths *)malloc(sizeof(t_all_paths));
	if (!new)
		exit(MALLOC_ERR);
	new->path = 0;
	new->path_weight = INT_MAX;
	new->ants_to_send = 0;
	new->next = 0;
	return (new);
}

t_path			*init_new_path(t_lemin *lemin)
{
	t_path			*new_path;

	new_path = (t_path *)malloc(sizeof(t_path));
	if (!new_path)
		exit(MALLOC_ERR);
	new_path->past_rooms = (void **)malloc(sizeof(void *) *
			(lemin->room_count + 1));
	ft_bzero(new_path->past_rooms, (sizeof(void *) * (lemin->room_count + 1)));
	new_path->past_rooms[0] = lemin->start;
	new_path->cur_link = 0;
	new_path->i = 1;
	new_path->q = queue_init();
	new_path->tree = gen_tree_init();
	new_path->room_to_check = 0;
	new_path->has_end = 0;
	new_path->handle_first_back_room = 0;
	return (new_path);
}

static t_path	*get_new_path(t_lemin *lemin)
{
	t_path			*path;

	path = init_new_path(lemin);
	path->tree->root = new_branch(lemin->start);
	enqueue(path->q, lemin->start);
	populate_path_start_room(lemin, path);
	populate_path(lemin, path);
	path->end_br = search_branch(path->tree->root, lemin->end);
	if (path->end_br)
	{
		add_parent_nodes_to_tree(path->tree);
		update_rooms_with_path_info(lemin, path);
	}
	else
	{
		free_path_struct(path);
		return (0);
	}
	return (path);
}

static void		add_path_to_all_path_list(t_lemin *lemin, t_all_paths *list,
		t_path *path)
{
	t_all_paths		*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp->path)
		tmp->path = convert_path_to_list(lemin, path);
	else
	{
		tmp->next = init_s_all_paths();
		tmp->next->path = convert_path_to_list(lemin, path);
	}
	free_path_struct(path);
	path = 0;
}

t_all_paths		*get_all_paths(t_lemin *lemin)
{
	t_all_paths			*list;
	t_path				*tmp;
	int					paths_found;

	list = init_s_all_paths();
	tmp = get_new_path(lemin);
	paths_found = 1;
	lemin->shortest_path = tmp;
	if (!tmp)
	{
		ft_dprintf(2, "No path to end room was found\n");
		exit(2);
	}
	while (tmp)
	{
		add_path_to_all_path_list(lemin, list, tmp);
		tmp = get_new_path(lemin);
		if (paths_found == lemin->total_ants || paths_found == 14)
			break ;
		paths_found++;
	}
	if (tmp)
		free_path_struct(tmp);
	return (list);
}
