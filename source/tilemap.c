/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilemap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 11:42:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 18:07:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "charmap.h"
#include "libft.h"
#include <stdlib.h>

#include "sl_test.h"

t_tilemap	*tilemap_init(t_plane dims)
{
	t_tilemap		*map;
	unsigned int	y;

	map = malloc(sizeof(t_tilemap));
	if (map == NULL)
		return (NULL);
	map->dims = dims;
	map->tiles = ft_calloc(map->dims.h, sizeof(t_object **));
	if (map->tiles == NULL)
		return (tilemap_destroy(&map), NULL);
	y = 0;
	while (y < map->dims.h)
	{
		map->tiles[y] = ft_calloc(map->dims.w, sizeof(t_object *));
		if (map->tiles[y++] == NULL)
			return (tilemap_destroy(&map), NULL);
	}
	return (map);
}

void	tilemap_set(t_tilemap *map, t_charmap *charmap)
{
	t_point		p;
	t_object	*obj;

	p.y = 0;
	while (p.y < map->dims.h)
	{
		p.x = 0;
		while (p.x < map->dims.w)
		{
			obj = object_init(charmap->objs[p.y][p.x]);
			if (obj)
			{
				map->tiles[p.y][p.x] = obj;
				obj->position = p;
			}
			p.x++;
		}
		p.y++;
	}
}

void	tilemap_destroy(t_tilemap **map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < (*map)->dims.h)
	{
		x = 0;
		while (x < (*map)->dims.w)
			object_destroy((*map)->tiles[y] + x++);
		y++;
	}
	free((*map)->tiles);
	free(*map);
	*map = NULL;
}
