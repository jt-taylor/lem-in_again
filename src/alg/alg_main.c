/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:23:04 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/25 17:49:05 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Explenation of the alg ::
** so this is edmonds karps but using going by node instead of by link
**
** we find the shortest path -- and disable those start && end link nodes
** we update the nodes from that path to say that 1 ant is moving forward on
** those nodes , and that we can send one ant backwards on them as well ;
**
** then we find the new shortest path ignoring the previously used start/end
** links , including all the others ;
** then we update the nodes from the new path to say that 1 ant is moving forward
** along it and one ant can move back through those nodes , but if a room already
** has an ant moving along it from the previous path we set the ants moving along
** it to 2 and and that 0 ants are allowed to move backwards through those rooms
** then we reapeat untill we can't construct a new path ;
**
** then we need to adjust the paths that share concurrent rooms , and only ever
** 2 paths will share the same room ;
** we also want to save a copy of the shortest path so that with small amounts
** of ants we can check if that is faster sending on one path
** than sending the max flow along concurrent paths ;
** then we calc the # of ants to send on each path ;; not sure exactly how i want
** to do that part yet ;
**
** and then we print the moves on the output ;
*/

int			alg_main(t_lemin *lemin)
{
	
}
