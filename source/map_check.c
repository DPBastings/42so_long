/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:04:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 12:55:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>

static bool	check_object(t_object *obj, int *reqs);

bool	map_check(t_map *map)
{
	return (map_check_walls(map)
		&& map_check_objects(map)
		&& map_check_path(map));
}

bool	map_check_walls(t_map *map)
{
	uint32_t	c;
	t_object	*obj;

	c = 0;
	while (c < map->dims.w)
	{
		obj = map->objs[0][c];
		if (obj == NULL || obj->type != OBJ_WALL)
			return (false);
		obj = map->objs[map->dims.h - 1][c];
		if (obj == NULL || obj->type != OBJ_WALL)
			return (false);
		c++;
	}
	c = 1;
	while (c < map->dims.h - 1)
	{
		obj = map->objs[c][0];
		if (obj == NULL || obj->type != OBJ_WALL)
			return (false);
		obj = map->objs[c][map->dims.w - 1];
		if (obj == NULL || obj->type != OBJ_WALL)
			return (false);
		c++;
	}
	return (true);
}

bool	map_check_objects(t_map *map)
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
				return (false);
			if (reqs & CHECK_COLL)
				return (true);
			p.x++;
		}
		p.y++;
	}
	return (reqs & CHECK_COLL);
}

static bool	check_object(t_object *obj, int *reqs)
{
	if (obj != NULL)
	{
		if (obj->type == OBJ_COLL)
			*reqs |= CHECK_COLL;
		else if (obj->type == OBJ_EXIT)
		{
			if (*reqs & CHECK_EXIT)
				return (false);
			*reqs |= CHECK_EXIT;
		}
		else if (obj->type == OBJ_PLYR)
		{
			if (*reqs & CHECK_PLYR)
				return (false);
			*reqs |= CHECK_PLYR;
		}
	}
	return (true);
}

uint32_t	map_get_maxscore(t_map *map)
{
	uint32_t	c;
	t_point		p;
	t_object	*obj;

	c = 0;
	p.y = 1;
	while (p.y < map->dims.h - 1)
	{
		p.x = 1;
		while (p.x < map->dims.w - 1)
		{
			obj = *map_index(map, p);
			if (obj && obj->type == OBJ_COLL)
				c++;
			p.x++;
		}
		p.y++;
	}
	return (c);
}
