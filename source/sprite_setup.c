/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 13:33:04 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"

static const t_spr_id		g_lkup_spr_id[N_OBJS] = {
	SPR_NONE,
	SPR_PLYR_IDLE,
	SPR_COLL_0,
	SPR_EXIT,
	SPR_WALL_0000,
	SPR_ENMY_MOVE_UP,
	SPR_ENMY_MOVE_UP,
	SPR_ENMY_MOVE_UP,
	SPR_NONE,
};
static const t_spr_setter	g_lkup_spr_setter[N_OBJS] = {
	sprite_set_default,
	sprite_set_default,
	sprite_set_coll,
	sprite_set_default,
	sprite_set_wall,
	sprite_set_enemy,
	sprite_set_enemy,
	sprite_set_enemy,
	NULL,
};

void	sprites_setup(t_game *game)
{
	t_upoint	p;
	t_object	*obj;

	p.y = 0;
	while (p.y < game->map->dims.y)
	{
		p.x = 0;
		while (p.x < game->map->dims.x)
		{
			obj = *map_index(game->map, p);
			if (obj)
				g_lkup_spr_setter[obj->type](obj, game);
			p.x++;
		}
		p.y++;
	}
}

void	sprite_set_default(t_object *obj, t_game *game)
{
	t_spr_id	id;

	id = g_lkup_spr_id[obj->type];
	sprite_change(obj, game->sprites[id], game);
}

void	sprite_set_coll(t_object *obj, t_game *game)
{
	t_spr_id	id;
	int32_t		x;

	if ((obj->position.x + obj->position.y) % 2 == 1)
		obj->z = Z_COLL1;
	x = game->seed / (obj->position.x * obj->position.y + 1);
	id = SPR_COLL_0 + (x % N_COLL_SPR);
	sprite_change(obj, game->sprites[id], game);
	obj->dir = ((x - (int32_t) obj->position.y) % 2 * 4);
	obj->sprite->image->instances[obj->instance_id].y += x % 8 - 4;
}

void	sprite_set_enemy(t_object *obj, t_game *game)
{
	t_spr_id	id;

	if (!object_is_passable(*map_index(game->map,
				upoint_get_adjacent(obj->position, obj->dir))))
		obj->dir = dir_invert(obj->dir);
	id = SPR_ENMY_MOVE_UP + obj->dir / 2;
	sprite_change(obj, game->sprites[id], game);
}
