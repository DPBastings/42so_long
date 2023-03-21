/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:04:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 17:06:48 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_map_check.h"
#include "sl_error.h"
#include "sl_object.h"

#include "libft.h"
#include "point.h"
#include <stddef.h>
#include <stdint.h>

typedef t_sl_errno	(*t_checkf)(t_map *);

static t_sl_errno	check_object(t_object *obj, int *reqs);

bool	map_check(t_map *map)
{
	t_sl_errno		errno;
	const t_checkf	checkers[N_MAP_CHECKS] = {
		map_check_walls,
		map_check_objects,
		map_check_path,};
	size_t			i;

	i = 0;
	while (i < 3)
	{
		errno = checkers[i](map);
		if (errno != SL_SUCCESS)
			sl_error(errno);
		i++;
	}
	return (true);
}

t_sl_errno	map_check_walls(t_map *map)
{
	uint32_t	c;

	c = 0;
	while (c < map->dims.x)
	{
		if (map->objs[0][c] == NULL
				|| map->objs[0][c]->type != OBJ_WALL
				|| map->objs[map->dims.y - 1][c] == NULL
				|| map->objs[map->dims.y - 1][c]->type != OBJ_WALL)
			return (SL_INVMAP_BOUNDS);
		c++;
	}
	c = 1;
	while (c < map->dims.y - 1)
	{
		if (map->objs[c][0] == NULL
				|| map->objs[c][0]->type != OBJ_WALL
				|| map->objs[c][map->dims.x - 1] == NULL
				|| map->objs[c][map->dims.x - 1]->type != OBJ_WALL)
			return (SL_INVMAP_BOUNDS);
		c++;
	}
	return (SL_SUCCESS);
}

t_sl_errno	map_check_objects(t_map *map)
{
	t_sl_errno	errno;
	t_upoint	p;
	int			reqs;

	reqs = 0;
	p.y = 1;
	while (p.y < map->dims.y - 1)
	{
		p.x = 1;
		while (p.x < map->dims.x - 1)
		{
			errno = check_object(map->objs[p.y][p.x], &reqs);
			if (errno != SL_SUCCESS)
				return (errno);
			p.x++;
		}
		p.y++;
	}
	if (!(reqs & CHECK_EXIT))
		return (SL_INVMAP_NOEXIT);
	if (!(reqs & CHECK_PLYR))
		return (SL_INVMAP_NOSTART);
	if (!(reqs & CHECK_COLL))
		return (SL_INVMAP_NOCOLL);
	return (SL_SUCCESS);
}

static t_sl_errno	check_object(t_object *obj, int *reqs)
{
	if (obj)
	{
		if (obj->type == OBJ_COLL)
			*reqs |= CHECK_COLL;
		else if (obj->type == OBJ_EXIT)
		{
			if (*reqs & CHECK_EXIT)
				return (SL_INVMAP_EXCEXIT);
			*reqs |= CHECK_EXIT;
		}
		else if (obj->type == OBJ_PLYR)
		{
			if (*reqs & CHECK_PLYR)
				return (SL_INVMAP_EXCSTART);
			*reqs |= CHECK_PLYR;
		}
	}
	return (SL_SUCCESS);
}

uint32_t	map_get_maxscore(t_map *map)
{
	uint32_t	c;
	t_upoint	p;
	t_object	*obj;

	c = 0;
	p.y = 1;
	while (p.y < map->dims.y - 1)
	{
		p.x = 1;
		while (p.x < map->dims.x - 1)
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
