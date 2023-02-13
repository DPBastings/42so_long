/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 15:08:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

#define BPP	4

static char const	*g_spritefiles[] = {
	"./assets/textures/wall.png",
	"./assets/textures/score.png",
	"./assets/textures/harpsichord.png",
	"./assets/textures/bach.png"
};

t_sprite	*sprite_load(mlx_t *mlx, char const *filename)
{
	t_sprite	*sprite;
	t_point		origin;
	t_plane		area;

	sprite = malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	sprite->texture = mlx_load_png(filename);
	if (sprite->texture == NULL || sprite->texture->width % GRID_W)
		sl_error(SL_BADASS);
	set_point(&origin, 0, 0);
	set_plane(&area, GRID_W, GRID_H);
	sprite->image = mlx_texture_area_to_image(mlx, sprite->texture,
		(unsigned int *)&origin, (unsigned int *)&area);
	if (sprite->image == NULL)
		return (mlx_delete_texture(sprite->texture), free(sprite), NULL);
	return (sprite);
}

t_sprite	**sprites_load(mlx_t *mlx)
{
	t_sprite		**sprites;
	size_t			i;

	i = 0;
	sprites = ft_calloc(N_SPRITES, sizeof(t_sprite *));
	if (sprites == NULL)
		sl_error(SL_MEMFAIL);
	while (i < N_SPRITES)
	{
		sprites[i] = sprite_load(mlx, g_spritefiles[i]);
		if (sprites[i] == NULL)
		{
			sprites_destroy(mlx, &sprites);
			sl_error(SL_MEMFAIL);
		}
		i++;
	}
	return (sprites);
}

void	sprite_animate(t_sprite *sprite, unsigned int frame)
{
	unsigned char	*pxsrc;
	unsigned char	*pxdst;
	unsigned int	x;
	unsigned int	y;

	x = frame * GRID_W % sprite->texture->width;
	y = 0;
	while (y < sprite->image->height)
	{
		pxsrc = &sprite->texture->pixels[y * sprite->texture->width + x * BPP];
		pxdst = &sprite->image->pixels[y * GRID_H * BPP];
		ft_memmove(pxdst, pxsrc, GRID_W * BPP);
		y++;
	}
}

void	sprites_destroy(mlx_t *mlx, t_sprite ***sprites)
{
	size_t	i;

	i = 0;
	while (i < N_SPRITES)
		sprite_destroy(mlx, &(*sprites)[i++]);
	free(*sprites);
	*sprites = NULL;
}

void	sprite_destroy(mlx_t *mlx, t_sprite **sprite)
{
	(void) mlx;
	mlx_delete_texture((*sprite)->texture);
	free(*sprite);
	*sprite = NULL;
}
