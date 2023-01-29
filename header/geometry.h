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

typedef struct	s_point {
	int	x;
	int	y;
}	t_point;

typedef struct	s_plane {
	int	w;
	int	h;
}	t_plane;

t_point	get_point(int x, int y);
t_plane	get_plane(int w, int h);

#endif
