/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_adapt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:34:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 16:55:10 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"

t_spr_id	sprite_adapt_coll(t_object *obj, void *param)
{
	t_game	*game;
	int32_t	factor;

	game = param;
	factor = game->seed / (obj->position.x * obj->position.y + 1);
	obj->dir = ((factor - (int32_t) obj->position.y) % 2 * 2);
	//obj->sprite->image->instances[obj->instance_id].y += (factor % 8 - 4);
	return (factor % N_COLL_SPR);
}

t_spr_id	sprite_adapt_wall(t_object *obj, void *param)
{
	t_game		*game;
	t_dir		dir;
	t_spr_id	offset;
	t_object	*adj;

	game = param;
	offset = 0;
	dir = 0;
	while (dir < N_DIRS)
	{
		offset <<= 1;
		adj = *map_index(game->map, point_get_adjacent(obj->position, dir));
		if (!(adj && (adj->type == OBJ_WALL || adj == game->NOWHERE)))
			offset++;
		dir++;
	}
	return (offset);
}
