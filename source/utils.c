/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 12:52:47 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 12:53:39 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include "MLX42/MLX42.h"

t_dir	dir_invert(t_dir dir)
{
	if (dir >= N_DIR / 2)
		return (dir - N_DIR / 2);
	return (dir + N_DIR / 2);
}

t_point	instance_to_point(mlx_instance_t instance)
{
	t_point	p;

	set_point(&p, instance.x, instance.y);
	return (p);
}
