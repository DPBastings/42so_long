/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:04:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 15:25:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "libftprintf.h"

int	map_check_walls(t_map *map)
{
	unsigned int	c;

	c = 0;
	while (c < map->dims.w)
	{
		if (map->objs[0][c]->type != OBJ_WALL
				|| map->objs[map->dims.h - 1][c]->type != OBJ_WALL)
			return (0);
		c++;
	}
	c = 1;
	while (c < map->dims.h - 1)
	{
		if (map->objs[c][0]->type != OBJ_WALL
				|| map->objs[c][map->dims.w - 1]->type != OBJ_WALL)
			return (0);
		c++;
	}
	return (1);
}

static int	check_object(t_object *obj, int *reqs)
{
	if (obj != NULL)
	{
		if (obj->type == OBJ_COLL)
			*reqs |= CHECK_COLL;
		else if (obj->type == OBJ_EXIT)
		{
			if (*reqs & CHECK_EXIT)
				return (0);
			*reqs |= CHECK_EXIT;
		}
		else if (obj->type == OBJ_PLYR)
		{
			if (*reqs & CHECK_PLYR)
				return (0);
			*reqs |= CHECK_PLYR;
		}
	}
	return (1);
}

int	map_check_objects(t_map *map)
{
	int			reqs;
	t_point		p;

	reqs = 0;
	p.y = 1;
	while (p.y < map->dims.h - 1)
	{
		p.x = 1;
		while (p.x < map->dims.w - 1)
		{
			if (!check_object(map->objs[p.y][p.x], &reqs))
				return (0);
			p.x++;
		}
		p.y++;
	}
	return (reqs & CHECK_COLL);
}

int	map_check(t_map *map)
{
	return (map_check_walls(map)
		&& map_check_objects(map)
		&& map_check_path(map));
}
