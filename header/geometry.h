/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   geometry.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 12:21:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:36:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include <stddef.h>
# include <stdint.h>

typedef enum e_axis {
	X = 0,
	Y,
	N_DIM,
}	t_axis;

typedef struct s_point {
	int32_t	x;
	int32_t	y;
}	t_point;

typedef struct s_upoint {
	uint32_t	x;
	uint32_t	y;
}	t_upoint;

typedef struct s_plane {
	unsigned int	w;
	unsigned int	h;
}	t_plane;

t_point		*set_point(t_point *point, int32_t x, int32_t y);
t_upoint	*set_upoint(t_upoint *upoint, uint32_t x, uint32_t y);
t_plane		*set_plane(t_plane *plane, unsigned int w, unsigned int h);

#endif
