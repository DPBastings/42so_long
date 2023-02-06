#include "sl_test.h"
#include "charmap.h"
#include "geometry.h"
#include "so_long.h"

#include "libftprintf.h"

void	charmap_view(t_charmap *map)
{
	size_t	i;

	i = 0;
	ft_printf("w = %u, h = %u\n", map->dims.w, map->dims.h);
	while (i < map->dims.h)
		ft_printf("%s", map->objs[i++]);
}

void	tilemap_view(t_tilemap *map)
{
	t_point		p;
	t_object	*obj;

	p.y = 0;
	while (p.y < map->dims.h)
	{
		p.x = 0;
		while (p.x < map->dims.w)
		{
			obj = map->tiles[p.y][p.x];
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
