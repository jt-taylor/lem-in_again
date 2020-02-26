/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:18:44 by jtaylor           #+#    #+#             */
/*   Updated: 2020/02/06 17:12:34 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** so because we are supposed to print the input file we can either add putstr
** for each time that we get_next_line from the input file or add a wrapper to
** the get_next_line, or read the whole file then print it to stdin then read it
** again
*/

/*
** this is a wrapper that just calls gnl and prints the string
*/

int		get_next_line_wrap(int fd, char **line)
{
	int		return_value;

	return_value = get_next_line(fd, line);
	if (return_value)
	{
		ft_putstr(line[0]);
		write(1, "\n", 1);
	}
	return (return_value);
}
