/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup_wall.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:33:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 15:03:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_graphics.h"
#include "sl_sprite_setup.h"
#include "sl_utils.h"

#include <stdint.h>

static void		check_sides(t_spr_id *id, t_object *obj, t_map *map);
static uint8_t	check_corners(t_spr_id id, t_object *obj, t_map *map);

void	sprite_set_wall(t_object *obj, t_game *game)
{
	t_spr_id	id;
	uint8_t		corners;

	id = 0;
	check_sides(&id, obj, game->map);
	corners = check_corners(~id, obj, game->map);
	if (corners)
	{
		if (id == 0)
			id = corners;
		else
			id = SPR_WALL_JUNC - SPR_WALL_MIN;
	}
	else if (id)
		id += SPR_WALL_JUNC - SPR_WALL_MIN;
	id += SPR_WALL_MIN;
	sprite_change(obj, game->sprites[id], game);
}

static void	check_sides(t_spr_id *id, t_object *obj, t_map *map)
{
	t_dir		dir;
	t_object	*adj;

	dir = 0;
	while (dir < N_DIRS)
	{
		*id <<= 1;
		adj = *map_index(map, upoint_get_adjacent(obj->position, dir));
		if (!(adj && (adj->type == OBJ_WALL || adj == map->none)))
			(*id)++;
		dir += 2;
	}
}

static uint8_t	check_corners(t_spr_id id, t_object *obj, t_map *map)
{
	uint8_t			corners;
	t_dir			dir;
	t_object		*adj;
	uint8_t const	sides[N_DIRS / 2] = {12, 6, 3, 9};

	corners = 0;
	dir = 0;
	while (dir < N_DIRS)
	{
		corners <<= 1;
		adj = *map_index(map, upoint_get_adjacent(obj->position, dir + 1));
		if (!(adj && (adj->type == OBJ_WALL || adj == map->none))
			&& (id & sides[dir / 2]) == sides[dir / 2])
			corners++;
		dir += 2;
	}
	return (corners);
}
