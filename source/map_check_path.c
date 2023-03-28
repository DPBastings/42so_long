/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 13:40:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/28 11:14:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_map_check.h"
#include "sl_error.h"
#include "sl_object.h"

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define UNCHECKED	-1
#define CHECKED		1

static void	check_point(t_upoint p, t_map *map,
				bool *check_exit, uint32_t *check_coll);
static void	map_clean(t_map *map);

/* bool map_check_path(t_map *map)
 * Determines whether `map` has an unobstructed path from the player's
 * starting position to the exit object.
 * Returns SL_INVMAP_NOPATH if there is no such path, returns SL_SUCCESS if
 * there is.
 */
t_sl_errno	map_check_path(t_map *map, uint32_t score_max)
{
	bool	exit_reachable;

	exit_reachable = false;
	map->none->instance_id = CHECKED;
	check_point(map->player->position, map, &exit_reachable, &score_max);
	map_clean(map);
	if (exit_reachable == false)
		return (SL_INVMAP_NOPATH_EXIT);
	if (score_max != 0)
		return (SL_INVMAP_NOPATH_COLL);
	return (SL_SUCCESS);
}

/* bool check_point(t_upoint p, t_map *map)
 * Checks if the exit has been reached; returns true if it has.
 * If the exit hasn't yet been reached, the current point is marked as checked
 * (either by setting a temporary flag on the object there or inserting a
 * reference to map->none in empty space) and the function calls itself for all 
 * adjacent passable, unchecked points.
 * Returns false if the map doesn't contain a reachable exit.
 */
static void	check_point(t_upoint p, t_map *map,
	bool *check_exit, uint32_t *check_coll)
{
	t_object	**obj;
	t_upoint	adj;
	t_dir		dir;

	obj = map_index(map, p);
	if (*obj)
	{
		if ((*obj)->instance_id == CHECKED)
			return ;
		if ((*obj)->type == OBJ_EXIT)
			*check_exit = true;
		else if ((*obj)->type == OBJ_COLL)
			*check_coll -= 1;
		(*obj)->instance_id = CHECKED;
	}
	else
		*obj = map->none;
	dir = 0;
	while (dir < N_DIRS)
	{
		adj = upoint_get_adjacent(p, dir);
		if (obj_is_passable(*map_index(map, adj)))
			check_point(adj, map, check_exit, check_coll);
		dir += 2;
	}
}

/* void	map_clean(t_map *map)
 * Cleans up after map_check_path has been executed: removes all references
 * to map->none in the map area and unsets the CHECKED flags for all non-NOWHERE
 * objects.
 */
static void	map_clean(t_map *map)
{
	t_upoint	p;
	t_object	**obj;

	p.y = 1;
	while (p.y < map->dims.y - 1)
	{
		p.x = 1;
		while (p.x < map->dims.x - 1)
		{
			obj = map_index(map, p);
			if (*obj)
			{
				if (*obj == map->none)
					*obj = NULL;
				else if ((*obj)->instance_id == CHECKED)
					(*obj)->instance_id = UNCHECKED;
			}
			p.x++;
		}
		p.y++;
	}
}
