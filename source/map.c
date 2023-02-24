/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 11:42:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:47:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

t_map	*map_init(t_plane dims)
{
	t_map		*map;
	uint32_t	y;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->dims = dims;
	map->objs = ft_calloc(map->dims.h, sizeof(t_object **));
	if (map->objs == NULL)
		return (map_destroy(&map), NULL);
	y = 0;
	while (y < map->dims.h)
	{
		map->objs[y] = ft_calloc(map->dims.w, sizeof(t_object *));
		if (map->objs[y] == NULL)
			return (map_destroy(&map), NULL);
		y++;
	}
	map->none = object_init(OBJ_NONE);
	if (map->none == NULL)
		return (map_destroy(&map), NULL);
	map->none->obj_below = map->none;
	return (map);
}

void	map_destroy(t_map **map)
{
	t_point		p;
	t_object	**slot;

	if (*map == NULL)
		return ;
	p.y = 0;
	while (p.y < (*map)->dims.h)
	{
		p.x = 0;
		while (p.x < (*map)->dims.w)
		{
			slot = map_index(*map, p);
			while (*slot)
				object_destroy(slot);
			p.x++;
		}
		free((*map)->objs[p.y]);
		p.y++;
	}
	free((*map)->objs);
	free((*map)->none);
	free(*map);
	*map = NULL;
}
