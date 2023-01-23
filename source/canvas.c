/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   canvas.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/20 12:04:57 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <mlx.h>
#include <stdlib.h>

t_canvas	*canvas_new(void *mlx_ptr, int width, int height)
{
	t_canvas	*new;

	new = malloc(sizeof(t_canvas));
	if (new == NULL)
		return (NULL);
	new->image = mlx_new_image(mlx_ptr, width, height);
	new->address = mlx_get_data_addr(new->image, 
										&(new->bpp), 
										&(new->len), 
										&(new->endian));
	if (new->image == NULL || new->address == NULL)
	{
		mlx_destroy_image(mlx_ptr, new->image);
		free(new->address);
		return (free(new), NULL);
	}
	return (new);
}

void	canvas_destroy(void *mlx_ptr, t_canvas *canvas)
{
	mlx_destroy_image(mlx_ptr, canvas->image);
	free(canvas->address);
	free(canvas);
}
