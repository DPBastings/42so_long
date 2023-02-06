/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 13:40:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/27 16:02:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "geometry.h"
#include "libft.h"
#include <stdlib.h>
#include <limits.h>

#define OBJ_CHECKED	'@'

/* t_point find_start()
 * Return the (topleftmost) point in `map` with the value OBJ_STRT.
 * Return UINT_MAX, UINT_MAX if no such point is found.*/
static t_point	find_start(t_map *map)
{
	t_point	start;
	
	start.y = 1;
	while (start.y < map->h - 1)
	{
		start.x = 1;
		while (start.x < map->w - 1)
		{
			if (map->objs[start.y][start.x] == OBJ_STRT)
				return (start);
			start.x++;
		}
		start.y++;
	}
	ft_memset(&start, UINT_MAX, sizeof(t_point));
	return (start);
}

/* t_point *get_adjacent(t_point point, t_map *map)
 * Return an array of the points adjacent to `point` within `map`. At most four
 * valid points are returned; nonexistent points (i.e. a point outside the map 
 * area) translate to x = UINT_MAX, y = UINT_MAX.
 * The memory at the address returned by this function is dynamically allocated
 * and must therefore be passed to free() once no longer in use.*/
static t_point *get_adjacent(t_point point, t_map *map)
{
	t_point	*adjacent;
	size_t	i;

	adjacent = malloc(4 * sizeof(t_point));
	if (adjacent == NULL)
		return (NULL);
	ft_memset(adjacent, UINT_MAX, 4 * sizeof(t_point));
	i = 0;
	if (point.y > 0)
		set_point(adjacent + i++, point.x, point.y - 1);
	if ((size_t) point.x < map->w - 1)
		set_point(adjacent + i++, point.x + 1, point.y);
	if ((size_t) point.y < map->h - 1)
		set_point(adjacent + i++, point.x, point.y + 1);
	if (point.x > 0)
		set_point(adjacent + i++, point.x - 1, point.y);
	return (adjacent);
}

/* int is_passable(t_point point, t_map *map)
 * Checks whether `point` in `map` constitutes passable and unchecked terrain
 * (i.e. has a value other than OBJ_WALL or OBJ_CHECKED).*/
static int	is_passable(t_point point, t_map *map)
{
	return (map->objs[point.y][point.x] != OBJ_WALL 
			&& map->objs[point.y][point.x] != OBJ_CHECKED);
}

static int	check_point(t_point point, t_map *map)
{
	t_point	*adjacent;
	size_t	i;
	int		res;

	if (map->objs[point.y][point.x] == OBJ_EXIT)
		return (1);
	adjacent = get_adjacent(point, map);
	if (adjacent == NULL)
		return (-1);
	map->objs[point.y][point.x] = OBJ_CHECKED;
	i = 0;
	while (i < 4)
	{
		if (is_passable(adjacent[i], map))
		{
			res = check_point(adjacent[i], map);
			if (res)
				return (free(adjacent), res);
		}
		i++;
	}
	return (free(adjacent), 0);
}

/* int map_check_path(t_map *map)
 * Determines whether `map` has an unobstructed path from the player's
 * starting position to the exit object.
 * Returns 0 if there is no such path, returns 1 if there is. Returns -1
 * on error.*/
int	map_check_path(t_map *map)
{
	t_point	start;
	t_map	*copy;
	int		res;

	copy = map_copy(map);
	if (copy == NULL)
		return (-1);
	start = find_start(copy);
	res = check_point(start, copy);
	map_destroy(&copy);
	return (res);
}
