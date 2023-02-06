/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   geometry.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 14:07:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 14:07:24 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_point	*set_point(t_point *point, unsigned int x, unsigned int y)
{
	point->x = x;
	point->y = y;
	return (point);
}

t_plane	*set_plane(t_plane *plane, unsigned int w, unsigned int h)
{
	plane->w = w;
	plane->h = h;
	return (plane);
}
