/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_assets.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 18:21:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <mlx.h>
#include <stdlib.h>

t_canvas	*load_texture(void *mlx_ptr, char const *file, t_plane dims)
{
	t_canvas	*texture;

	texture = malloc(sizeof(t_canvas));
	if (texture == NULL)
		return (NULL);
	texture->image = mlx_xpm_file_to_image(mlx_ptr, (char *)file, &dims.w, &dims.h);
	if (texture->image == NULL)
		return (free(texture), NULL);
	texture->address = mlx_get_data_addr(texture->image,
											&texture->bpp,
											&texture->len,
											&texture->endian);
	if (texture->address == NULL)
		return (mlx_destroy_image(mlx_ptr, texture->image), free(texture), NULL);
	return (texture);
}
