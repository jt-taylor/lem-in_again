/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_residual_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:58:03 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 20:44:51 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static inline void	toggle_to_use(t_lemin *lemin, t_path *path, t_branch
		*one_before_end)
{
	if (one_before_end->content == lemin->start)
		return ;
	if (one_before_end->kid == path->end_br)
		((t_rooms *)one_before_end->content)->to_use = 0;
	if (one_before_end->parent->content == lemin->start)
	{
		((t_rooms *)one_before_end->content)->to_use_start = 0;
	}
}

/*
** update_rooms_with_path_info-----------------------------------
** for the rooms on the current path, it will be toggled their use
** on the room after start and room before end to not use for
** the next path search, and for each room on the path that
** it's not the endroom or startroom, it will increase the forward
** value by 1 and swap the backward value between 1 and 0.
*/

void				update_rooms_with_path_info(t_lemin *lemin, t_path *path)
{
	t_branch		*tmp;

	tmp = path->end_br;
	while (tmp->parent)
	{
		if (tmp->kid == path->end_br || tmp->parent->content == lemin->start)
			toggle_to_use(lemin, path, tmp);
		if (tmp->content != lemin->start && tmp != path->end_br)
		{
			((t_rooms *)tmp->content)->forward += 1;
			((t_rooms *)tmp->content)->backward ^= 1;
		}
		tmp = tmp->parent;
	}
}
