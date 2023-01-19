#include "map.h"
#include "libftprintf.h"

static int	check_walls(t_map *map);
static int	check_object(t_map *map, int *reqs);
static int	check_path(t_map *map);

static int	check_walls(t_map *map)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = map->objs[i++];
	while (*ptr != '\n')
	{
		if (*(ptr++) != OBJ_WALL)
			return (0);
	}
	while (i < map->h - 1)
	{
		ptr = map->objs[i++];
		if (ptr[0] != OBJ_WALL || ptr[map->w - 1] != OBJ_WALL)
			return (0);
	}
	while (*ptr != '\n')
	{
		if (*(ptr++) != OBJ_WALL)
			return (0);
	}
	return (1);
}

static int	check_object(t_map *map, int *reqs)
{
	char	*slice;
	size_t	i;

	i = 1;
	while (i < map->h - 1)
	{
		slice = map->objs[i++];
		while (*slice != '\n')
		{
			if (*slice == OBJ_COLL)
				*reqs |= CHECK_COLL;
			else if (*slice == OBJ_EXIT)
			{
				if (*reqs & CHECK_EXIT)
					return (0);
				*reqs |= CHECK_EXIT;
			}
			else if (*slice == OBJ_STRT)
			{
				if (*reqs & CHECK_STRT)
					return (0);
				*reqs |= CHECK_STRT;
			}
		}
	}
	return (*reqs & CHECK_COLL);
}

static int	check_path(t_map *map)
{
	(void) map;
	return (1);
}

int	map_check(t_map *map)
{
	int		reqs;

	reqs = 0;
	ft_printf("%d\n", check_walls(map));//, check_object(map, &reqs));
	reqs = 0;
	return (check_walls(map)
		&& check_object(map, &reqs)
		&& check_path(map));
}
