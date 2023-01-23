/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 13:40:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/23 18:05:29 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "draw.h"
#include "libftprintf.h"

static t_point	find_start(t_map *map)
{
	t_point	start;
	
	start.y = 1;
	while ((size_t) start.y < map->h - 1)
	{
		start.x = 1;
		while ((size_t) start.x < map->w- 1)
		{
			if (map->objs[start.y][start.x] == OBJ_STRT)
				return (start);
			start.x++;
		}
		start.y++;
	}
	start.x = -1;
	start.y = -1;
	return (start);
}

int	map_check_path(t_map *map)
{
	t_point	start;

	start = find_start(map);
	ft_printf("Start at x=%d, y=%d\n", start.x, start.y);
	return (1);
}
