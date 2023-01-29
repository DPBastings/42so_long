#include "sl_test.h"
#include "map.h"

#include "libftprintf.h"

void	map_view(t_map *map)
{
	size_t	i;

	i = 0;
	ft_printf("w = %u, h = %u\n", map->w, map->h);
	while (i < map->h)
		ft_printf("%s", map->objs[i++]);
}
