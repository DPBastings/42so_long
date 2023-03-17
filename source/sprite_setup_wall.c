/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup_wall.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:33:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 17:03:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_sides(t_spr_id *id, t_object *obj, t_map *map);
static void	check_corners(t_spr_id *id, t_object *obj, t_map *map);

void	sprite_set_wall(t_object *obj, t_game *game)
{
	t_spr_id	id;

	id = 0;
	check_sides(&id, obj, game->map);
	check_corners(&id, obj, game->map);
	id += SPR_WALL_0000;
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

static void	check_corners(t_spr_id *id, t_object *obj, t_map *map)
{
	t_dir		dir;
	t_object	*adj;

	dir = 1;
	while (dir < N_DIRS)
	{
		adj = *map_index(map, upoint_get_adjacent(obj->position, dir));
		if (!(adj && (adj->type == OBJ_WALL || adj == map->none)) && *id == 0)
		{
			*id = 16;
			break ;
		}
		dir += 2;
	}
}
