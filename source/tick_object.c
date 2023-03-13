/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_object.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:01:08 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 11:33:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

static t_obj_ticker	g_lut_ticker[N_OBJS] = {
	tick_default,
	tick_player,
	tick_coll,
	tick_exit,
	tick_default,
	tick_enemy_easy,
	tick_enemy_easy,
	tick_enemy_hard,
	tick_default,
};

static void	tick(t_object *obj, void *param);
static void	tick_reset(t_object *obj);

void	objects_tick(t_game *game)
{
	t_upoint	p;

	p.y = 0;
	while (p.y < game->map->dims.y)
	{
		p.x = 0;
		while (p.x < game->map->dims.x)
		{
			tick(*map_index(game->map, p), game);
			p.x++;
		}
		p.y++;
	}
	p.y = 0;
	while (p.y < game->map->dims.y)
	{
		p.x = 0;
		while (p.x < game->map->dims.x)
		{
			tick_reset(*map_index(game->map, p));
			p.x++;
		}
		p.y++;
	}
}

static void	tick(t_object *obj, void *param)
{
	if (obj)
	{
		if (obj->ticked == false)
			g_lut_ticker[obj->type](obj, param);
		tick(obj->obj_below, param);
	}
}

static void	tick_reset(t_object *obj)
{
	if (obj)
	{
		obj->ticked = false;
		tick_reset(obj->obj_below);
	}
}
