/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 12:52:47 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 13:20:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include "MLX42/MLX42.h"

static const uint32_t	g_lut_dir[N_DIRS][N_DIM] = {
{0, -1},
{1, 0},
{0, 1},
{-1, 0},
};

void	instance_move(mlx_instance_t *instance, t_dir dir, uint32_t speed)
{
	instance->x += g_lut_dir[dir][X] * speed;
	instance->y += g_lut_dir[dir][Y] * speed;
}

t_dir	dir_invert(t_dir dir)
{
	return ((dir + N_DIRS / 2) % N_DIRS);
}

t_point	instance_to_point(mlx_instance_t instance)
{
	t_point	p;

	set_point(&p, instance.x, instance.y);
	return (p);
}

t_upoint	upoint_get_adjacent(t_upoint p, t_dir dir)
{
	p.x += g_lut_dir[dir][X];
	p.y += g_lut_dir[dir][Y];
	return (p);
}
