/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   geometry.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 12:21:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/27 14:50:27 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <stddef.h>

typedef struct	s_point {
	unsigned int	x;
	unsigned int	y;
}	t_point;

typedef struct	s_plane {
	unsigned int	w;
	unsigned int	h;
}	t_plane;

t_point	*set_point(t_point *point, unsigned int x, unsigned int y);
t_plane	*set_plane(t_plane *plane, unsigned int w, unsigned int h);

#endif
