/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:39:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"

static unsigned int	sprite_adapt_pass(t_object *obj, void *param);

static const int			g_spr_id_lookup[N_OBJS] = {
	SPR_NONE,
	SPR_PLYR,
	SPR_COLL_0,
	SPR_EXIT,
	SPR_WALL_1111
};
static const t_spr_adapter	g_spr_adapter_lookup[N_OBJS] = {
	sprite_adapt_pass,
	sprite_adapt_pass,
	sprite_adapt_coll,
	sprite_adapt_pass,
	sprite_adapt_wall,
};

void	sprites_setup(t_game *game)
{
	t_point		p;
	t_object	**obj;

	p.y = 0;
	while (p.y < game->map->dims.h)
	{
		p.x = 0;
		while (p.x < game->map->dims.w)
		{
			obj = map_index(game->map, p);
			sprite_setup(*obj, game);
			p.x++;
		}
		p.y++;
	}
}

void	sprite_setup(t_object *obj, t_game *game)
{
	t_spr_adapter	f;

	if (obj == NULL)
		return ;
	f = g_spr_adapter_lookup[obj->type];
	obj->sprite = game->sprites[g_spr_id_lookup[obj->type] + f(obj, game)];
	obj->instance_id = mlx_image_to_window(game->mlx,
			obj->sprite->image,
			obj->position.x * GRID_W, obj->position.y * GRID_H);
	if (obj->instance_id == -1)
		sl_error(SL_MEMFAIL);
}

static unsigned int	sprite_adapt_pass(t_object *obj, void *param)
{
	(void) obj;
	(void) param;
	return (0);
}
