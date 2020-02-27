/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:17:13 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/26 20:40:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_path_struct(t_path *path)
{
	if (!path)
		exit(CLEANUP_ERR);
	free(path->past_rooms);
	free_queue_contents(0, path->q);
	free_lemin_tree(path->tree);
	free(path);
	path = 0;
}
