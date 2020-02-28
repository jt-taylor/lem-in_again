/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path_helper_func.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:31:04 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/27 18:31:15 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			get_path_limits(t_path_list *p1, t_path_list *p2,
		t_split_path *s)
{
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
