/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 12:52:47 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 10:35:58 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include "MLX42/MLX42.h"

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
