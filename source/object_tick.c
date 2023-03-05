/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:01:08 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 14:06:26 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

static t_obj_ticker	g_lookup_ticker[N_OBJS] = {
	object_tick_default,
	object_tick_player,
	object_tick_coll,
	object_tick_exit,
	object_tick_default,
	object_tick_default,
};

static void	object_tick(t_object *obj, void *param);
static void	object_tick_reset(t_object *obj);

void	objects_tick(t_game *game)
{
	t_upoint	p;

	p.y = 0;
	while (p.y < game->map->dims.y)
	{
		p.x = 0;
		while (p.x < game->map->dims.x)
		{
			object_tick(*map_index(game->map, p), game);
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
			object_tick_reset(*map_index(game->map, p));
			p.x++;
		}
		p.y++;
	}
}

static void	object_tick(t_object *obj, void *param)
{
	if (obj)
	{
		if (obj->ticked == false)
			g_lookup_ticker[obj->type](obj, param);
		object_tick(obj->obj_below, param);
	}
}

static void	object_tick_reset(t_object *obj)
{
	if (obj)
	{
		obj->ticked = false;
		object_tick_reset(obj->obj_below);
	}
}
