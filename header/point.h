/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:24:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 11:24:36 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

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

t_point		*set_point(t_point *point, int32_t x, int32_t y);
t_upoint	*set_upoint(t_upoint *upoint, uint32_t x, uint32_t y);

#endif
