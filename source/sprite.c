/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
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

static const int	g_txr_id_lookup[N_SPRITES] = {
	TXR_NONE,
	TXR_PLYR,
	TXR_COLL,
	TXR_COLL,
	TXR_COLL,
	TXR_COLL,
	TXR_COLL,
	TXR_COLL,
	TXR_EXIT,
	TXR_WALL,
};

t_sprite	**sprites_init(t_game *game)
{
	t_sprite		**sprites;
	unsigned int	id;

	sprites = ft_calloc(N_SPRITES, sizeof(t_sprite *));
	if (sprites == NULL)
		sl_error(SL_MEMFAIL);
	id = 1;
	while (id < N_SPRITES)
	{
		sprites[id] = sprite_new(game, id);
		if (sprites[id] == NULL)
		{
			sprites_destroy(&sprites);
			sl_error(SL_MEMFAIL);
		}
		id++;
	}
	return (sprites);
}

t_sprite	*sprite_new(t_game *game, unsigned int spr_id)
{
	t_sprite		*sprite;
	unsigned int	txr_id;
	t_texture		*texture;

	txr_id = g_txr_id_lookup[spr_id];
	texture = game->textures[txr_id];
	if (txr_id == TXR_COLL)
		sprite = sprite_load(texture, game->mlx,
				0, (SPR_COLL_MAX - spr_id) * (GRID_H / (SPR_COLL_MAX - SPR_COLL_0)));
	else if (txr_id == TXR_WALL)
		sprite = sprite_load(texture, game->mlx,
				SPR_WALL_1111 - spr_id, 0);
	else
		sprite = sprite_load(texture, game->mlx, 0, 0);
	return (sprite);
}

t_sprite	*sprite_load(t_texture *texture, mlx_t *mlx,
	unsigned int origin_i, unsigned int frame)
{
	t_sprite	*sprite;
	t_point		origin;
	t_plane		area;

	if (texture == NULL)
		return (NULL);
	sprite = malloc(sizeof(t_sprite));
	if (sprite == NULL)
		return (NULL);
	sprite->mlx = mlx;
	set_point(&origin, origin_i * GRID_W, 0);
	set_plane(&area, GRID_W, GRID_H);
	sprite->image = mlx_texture_area_to_image(sprite->mlx, texture->texture,
			(unsigned int *)&origin, (unsigned int *)&area);
	if (sprite->image == NULL)
		return (free(sprite), NULL);
	sprite->frame = frame;
	return (sprite);
}

void	sprites_destroy(t_sprite ***sprites)
{
	size_t	i;

	i = 1;
	while (i < N_SPRITES)
		sprite_destroy(&(*sprites)[i++]);
	free(*sprites);
	*sprites = NULL;
}

void	sprite_destroy(t_sprite **sprite)
{
	if (*sprite == NULL)
		return ;
	mlx_delete_image((*sprite)->mlx, (*sprite)->image);
	free(*sprite);
	*sprite = NULL;
}

/*void	sprite_animate(t_sprite *sprite, uint32_t frame)
{
	uint8_t	*src;
	uint8_t	*dst;
	t_point	p;

	p.x = frame * GRID_W % sprite->texture->width;
	p.y = 0;
	while (p.y < sprite->image->height)
	{
		src = &sprite->texture->pixels[p.y * sprite->texture->width + p.x * BPP];
		dst = &sprite->image->pixels[p.y * GRID_H * BPP];
		ft_memmove(dst, src, GRID_W * BPP);
		y++;
	}
}*/
