/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:32:54 by marrodri          #+#    #+#             */
/*   Updated: 2020/02/27 21:32:55 by marrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_all_paths(t_all_paths *path_list)
{
	t_all_paths		*head;
	struct s_node	*head_path;
	t_rooms			*room;

	head = path_list;
	head_path = head->path->first;
	while (head)
	{
		ft_printf("================\n");
		while (head_path)
		{
			room = (t_rooms*)head_path->content;
			ft_printf("[%s]", (char*)(room)->room_name);
			head_path = head_path->next;
			if (head_path)
				ft_printf("-");
			else if (!head_path)
				ft_printf("\n");
		}
		head = head->next;
		head_path = head->path->first;
	}
}
