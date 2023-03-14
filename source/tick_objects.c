/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:01:08 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 12:58:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

static void	obj_tick(t_object **obj, t_game *game);
static void	obj_tick_reset(t_object *obj);

void	objects_tick(t_game *game)
{
	t_upoint	p;

	p.y = 0;
	while (p.y < game->map->dims.y)
	{
		p.x = 0;
		while (p.x < game->map->dims.x)
		{
			obj_tick(map_index(game->map, p), game);
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
			obj_tick_reset(*map_index(game->map, p));
			p.x++;
		}
		p.y++;
	}
}

void	obj_tick(t_object **obj, t_game *game)
{
	const t_obj_ticker	lut_ticker[N_OBJS] = {
		tick_default,
		tick_player,
		tick_coll,
		tick_exit,
		tick_default,
		tick_enemy_easy,
		tick_enemy_easy,
		tick_enemy_hard,
		tick_default,};

	if (*obj && (*obj)->ticked == false)
		lut_ticker[(*obj)->type](*obj, game);
	if (*obj)
		obj_tick(&(*obj)->below, game);
}

static void	obj_tick_reset(t_object *obj)
{
	if (obj)
	{
		obj->ticked = false;
		obj_tick_reset(obj->below);
	}
}
