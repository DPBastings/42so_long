/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 13:40:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:16:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"
#include "libft.h"
#include <stdlib.h>
#include <limits.h>

#define UNCHECKED	0
#define CHECKED		1

static int		check_point(t_point p, t_map *map);
static void		map_clean(t_map *map);

/* int map_check_path(t_map *map)
 * Determines whether `map` has an unobstructed path from the player's
 * starting position to the exit object.
 * Returns 0 if there is no such path, returns 1 if there is.
 */
int	map_check_path(t_map *map)
{
	int			res;

	res = check_point(map->player->position, map);
	map_clean(map);
	return (res);
}

/* int check_point(t_point p, t_map *map)
 * Checks if the exit has been reached; returns 1 if it has.
 * If the exit hasn't yet been reached, the current point is marked as checked
 * (either by setting a temporary flag on the object there or inserting a
 * reference to NOWHERE in empty space) and the function calls itself for all 
 * adjacent passable, unchecked points.
 * Returns 0 if the map doesn't contain a reachable exit.
 */
static int	check_point(t_point p, t_map *map)
{
	t_object	**obj;
	t_point		*adj;
	size_t		i;

	obj = map_index(map, p);
	if (*obj)
	{
		if ((*obj)->type == OBJ_EXIT)
			return (1);
		(*obj)->id = CHECKED;
	}
	else
		*obj = NOWHERE;
	adj = map_get_adjacent(map, p);
	i = 0;
	while (i < N_DIRS)
	{
		if (object_is_passable(*map_index(map, adj[i]))
			&& check_point(adj[i], map))
			return (free(adj), 1);
		i++;
	}
	return (free(adj), 0);
}

/* void	map_clean(t_map *map)
 * Cleans up after map_check_path has been executed: removes all references
 * to NOWHERE in the map area and unsets the CHECKED flags for all non-NOWHERE
 * objects.
 */
static void	map_clean(t_map *map)
{
	t_point		p;
	t_object	**obj;

	p.y = 1;
	while (p.y < map->dims.h - 1)
	{
		p.x = 1;
		while (p.x < map->dims.w - 1)
		{
			obj = map_index(map, p);
			if (*obj)
			{
				if (*obj == NOWHERE)
					*obj = NULL;
				else if ((*obj)->id == CHECKED)
					(*obj)->id = UNCHECKED;
			}
			p.x++;
		}
		p.y++;
	}
}
