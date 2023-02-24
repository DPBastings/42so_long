/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 16:15:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

// Lookup table for various t_sprite variables.
// <texture ID>	<frame_max>
typedef enum e_spr_param {
	P_TXR_ID = 0,
	P_FRAME_MAX,
	N_SPR_PARAM,
}	t_spr_param;
static const uint32_t	g_lookup_spr_param[N_SPRITES * N_SPR_PARAM] = {
	TXR_NONE,		0,
	TXR_PLYR,		0,
	TXR_PLYR_IDLE,	12,
	TXR_PLYR_WALK,	12,
	TXR_PLYR_WALK,	12,
	TXR_PLYR_WALK,	12,
	TXR_PLYR_WALK,	12,
	TXR_COLL,		-1,
	TXR_COLL,		-1,
	TXR_COLL,		-1,
	TXR_COLL,		-1,
	TXR_COLL,		-1,
	TXR_COLL,		-1,
	TXR_EXIT,		-1,
	TXR_WALL,		0,
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
			sprites_destroy(&sprites, game->mlx);
			sl_error(SL_MEMFAIL);
		}
		id++;
	}
	return (sprites);
}

t_sprite	*sprite_new(t_game *game, uint32_t spr_id)
{
	t_sprite	*sprite;
	uint32_t	txr_id;
	t_texture	*texture;

	txr_id = g_lookup_spr_param[spr_id * N_SPR_PARAM + P_TXR_ID];
	texture = game->textures[txr_id];
	if (txr_id == TXR_COLL)
		sprite = sprite_load(texture, game->mlx, 0,
				(SPR_COLL_MAX - spr_id) * (GRID_W / N_COLL_SPR));
	else if (txr_id == TXR_WALL)
		sprite = sprite_load(texture, game->mlx,
				SPR_WALL_1111 - spr_id, 0);
	else
		sprite = sprite_load(texture, game->mlx, 0, 0);
	sprite->frame_max = g_lookup_spr_param[spr_id * N_SPR_PARAM + P_FRAME_MAX];
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
	sprite->texture = texture;
	set_point(&origin, origin_i * GRID_W, 0);
	set_plane(&area, GRID_W, GRID_H);
	sprite->image = mlx_texture_area_to_image(mlx, texture,
			(unsigned int *)&origin, (unsigned int *)&area);
	if (sprite->image == NULL)
		return (free(sprite), NULL);
	sprite->frame = frame;
	return (sprite);
}

void	sprites_destroy(t_sprite ***sprites, mlx_t *mlx)
{
	size_t	i;

	if (*sprites == NULL)
		return ;
	i = 1;
	while (i < N_SPRITES)
		sprite_destroy(&(*sprites)[i++], mlx);
	free(*sprites);
	*sprites = NULL;
}

void	sprite_destroy(t_sprite **sprite, mlx_t *mlx)
{
	if (*sprite == NULL)
		return ;
	mlx_delete_image(mlx, (*sprite)->image);
	free(*sprite);
	*sprite = NULL;
}
