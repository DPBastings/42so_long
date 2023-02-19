/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:17:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static char const	*g_texture_files[] = {
	"",
	"./assets/textures/bach.png",
	"./assets/textures/orb.png",
	"./assets/textures/harpsichord.png",
	"./assets/textures/wall.png",
};

t_texture	**textures_load(t_game *game)
{
	t_texture	**textures;
	size_t		i;

	i = 1;
	textures = ft_calloc(N_TEXTURES, sizeof(t_texture *));
	if (textures == NULL)
		sl_error(SL_MEMFAIL);
	while (i < N_TEXTURES)
	{
		textures[i] = texture_load(g_texture_files[i]);
		if (textures[i] == NULL)
		{
			textures_destroy(&textures);
			sl_error(SL_MEMFAIL);
		}
		if (i == 1)
			textures[i]->gradient = game->gradient;
		else
			textures[i]->gradient = NULL;
		i++;
	}
	return (textures);
}

t_texture	*texture_load(char const *filename)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (texture == NULL)
		return (NULL);
	texture->texture = mlx_load_png(filename);
	if (texture->texture == NULL || texture->texture->width % GRID_W)
		sl_error(SL_BADASS);
	return (texture);
}

void	textures_destroy(t_texture ***textures)
{
	size_t	i;

	i = 0;
	while (i < N_SPRITES)
		texture_destroy(&(*textures)[i++]);
	free(*textures);
	*textures = NULL;
}

void	texture_destroy(t_texture **texture)
{
	mlx_delete_texture((*texture)->texture);
	free(*texture);
	*texture = NULL;
}
