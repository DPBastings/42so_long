/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 18:21:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static char const	*g_spritefiles[] = {
	"./assets/textures/wall.png",
	"./assets/textures/bach.png",
	"./assets/textures/score.png",
	"./assets/textures/harpsichord.png"
};

static t_point	*setpoint(t_point *point, unsigned int x, unsigned int y)
{
	point->x = x;
	point->y = y;
	return (point);
}

static t_plane	*setplane(t_plane *plane, unsigned int w, unsigned int h)
{
	plane->w = w;
	plane->h = h;
	return (plane);
}

void	sprite_destroy(mlx_t *mlx, t_sprite **sprite)
{
	mlx_delete_texture((*sprite)->texture);
	mlx_delete_image(mlx, (*sprite)->image);
	free(*sprite);
	*sprite = NULL;
}

t_sprite	*sprite_load(mlx_t *mlx, char const *filename)
{
	t_sprite	*sprite;
	t_point		origin;
	t_plane		area;

	sprite = malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	sprite->texture = mlx_load_png(filename);
	if (sprite->texture == NULL)
		return (free(sprite), NULL);
	setpoint(&origin, 0, 0);
	setplane(&area, GRID_SIZE, GRID_SIZE);
	sprite->image = mlx_texture_area_to_image(mlx, sprite->texture,
			(unsigned int *)&origin, (unsigned int *)&area);
	if (sprite->image == NULL)
		return (mlx_delete_texture(sprite->texture), free(sprite), NULL);
	return (sprite);
}

t_sprite	**load_sprites(mlx_t *mlx)
{
	t_sprite		**sprites;
	size_t			i;

	i = 0;
	sprites = ft_calloc(N_SPRITES, sizeof(t_sprite*));
	if (sprites == NULL)
		return (NULL);
	while (i < N_SPRITES)
	{
		sprites[i] = sprite_load(mlx, g_spritefiles[i]);
		if (sprites[i] == NULL)
		{
			i = 0;
			while (i < N_SPRITES)
				sprite_destroy(mlx, sprites + i++);
			return (NULL);
		}
		i++;
	}
	return (sprites);
}
