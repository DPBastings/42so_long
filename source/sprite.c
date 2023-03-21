/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 15:43:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_graphics.h"
#include "sl_general.h"
#include "sl_error.h"
#include "sl_image.h"

#include "libft.h"
#include "point.h"
#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdlib.h>

#define GRID_W 48
#define GRID_H 48

enum e_spr_param {
	TXR_ID = 0,
	START_FRAME,
	FRAME_MAX,
	N_PARAM,
};

static const uint32_t	g_lut_spr_param[N_SPRITES][N_PARAM] = {
{TXR_NONE,			0,	0,},
{TXR_PLYR_IDLE,		0,	13,},
{TXR_PLYR_WALK_U,	0,	12,},
{TXR_PLYR_WALK_R,	0,	12,},
{TXR_PLYR_WALK_D,	0,	12,},
{TXR_PLYR_WALK_L,	0,	12,},
{TXR_ENMY_WALK_U,	0,	12,},
{TXR_ENMY_WALK_R,	0,	12,},
{TXR_ENMY_WALK_D,	0,	12,},
{TXR_ENMY_WALK_L,	0,	12,},
{TXR_COLL,			0,	-1,},
{TXR_COLL,			16,	-1,},
{TXR_COLL,			32,	-1,},
{TXR_COLL,			48,	-1,},
{TXR_COLL,			64,	-1,},
{TXR_COLL,			80,	-1,},
{TXR_EXIT,			0,	0,},
{TXR_VORTEX,		0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_WALL,			0,	0,},
{TXR_BG,			0,	0,},};

static t_sprite	*sprite_init(mlx_t *mlx, t_spr_id id, mlx_texture_t **txrs);
static void		spr_texture_read(mlx_image_t *img, mlx_texture_t *txr,
					t_spr_id id);
static void		sprite_destroy(t_sprite **sprite, mlx_t *mlx);

t_sprite	**sprites_init(mlx_t *mlx, mlx_texture_t **txrs)
{
	t_sprite	**sprites;
	t_spr_id	id;

	sprites = ft_calloc(N_SPRITES, sizeof(t_sprite *));
	if (sprites == NULL)
		sl_error(SL_MEMFAIL);
	id = 1;
	while (id < N_SPRITES)
	{
		sprites[id] = sprite_init(mlx, id, txrs);
		id++;
	}
	return (sprites);
}

void	sprites_destroy(t_sprite ***sprites, mlx_t *mlx)
{
	t_spr_id	id;

	if (*sprites == NULL)
		return ;
	id = 1;
	while (id < N_SPRITES)
		sprite_destroy(&(*sprites)[id++], mlx);
	free(*sprites);
	*sprites = NULL;
}

static t_sprite	*sprite_init(mlx_t *mlx, t_spr_id id, mlx_texture_t **txrs)
{
	t_sprite	*spr;

	spr = malloc(sizeof(t_sprite));
	if (spr == NULL)
		sl_error(SL_MEMFAIL);
	spr->texture = txrs[g_lut_spr_param[id][TXR_ID]];
	spr->image = image_init(mlx, GRID_W, GRID_H);
	spr_texture_read(spr->image, spr->texture, id);
	spr->frame = g_lut_spr_param[id][START_FRAME];
	spr->frame_max = g_lut_spr_param[id][FRAME_MAX];
	if (spr->frame_max == 0)
		spr->animator = sprite_animate_pass;
	else if (id >= SPR_COLL_0 && id <= SPR_COLL_MAX)
		spr->animator = sprite_animate_coll;
	else
		spr->animator = sprite_animate;
	return (spr);
}

static void	spr_texture_read(mlx_image_t *img, mlx_texture_t *txr, t_spr_id id)
{
	t_upoint	dst;
	t_upoint	src;

	set_upoint(&dst, 0, 0);
	set_upoint(&src, 0, 0);
	if (id >= SPR_WALL_MIN && id <= SPR_WALL_MAX)
		src.x = (id - SPR_WALL_MIN) * GRID_W;
	texture_area_copy_to_image(img, txr, (uint32_t *)&dst, (uint32_t *)&src);
}

static void	sprite_destroy(t_sprite **sprite, mlx_t *mlx)
{
	if (*sprite == NULL)
		return ;
	mlx_delete_image(mlx, (*sprite)->image);
	free(*sprite);
	*sprite = NULL;
}
