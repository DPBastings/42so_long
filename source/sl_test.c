/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_test.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:22:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:22:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_test.h"
#include "geometry.h"
#include "so_long.h"

#include "libftprintf.h"

void	adj_view(t_point *adj)
{
	size_t	i;

	i = 0;
	while (i < N_DIRS)
	{
		ft_printf("%p: ", &adj[i]);
		ft_printf("%u %u\n", adj[i].x, adj[i].y);
		i++;
	}
}

void	map_view(t_map *map)
{
	t_point		p;
	t_object	*obj;

	ft_printf("Map at %p (%u x %u tiles):\n", map, map->dims.h, map->dims.w);
	p.y = 0;
	while (p.y < map->dims.h)
	{
		p.x = 0;
		while (p.x < map->dims.w)
		{
			obj = map->objs[p.y][p.x];
			if (obj)
			{
				if (obj == NOWHERE)
					ft_printf("@");
				else
					ft_printf("%d", obj->type);
			}
			else
				ft_printf(" ");
			p.x++;
		}
		ft_printf("\n");
		p.y++;
	}
}
