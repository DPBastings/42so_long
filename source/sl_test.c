#include "sl_test.h"
#include "geometry.h"
#include "so_long.h"

#include "libftprintf.h"

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
				ft_printf("%d", obj->type);
			else
				ft_printf(" ");
			p.x++;
		}
		ft_printf("\n");
		p.y++;
	}
}
