#include "map.h"

static int	check_owalls(char const *line);
static int	check_iwalls(char const *line);
static int	check_object(char const *line);
static int	check_path(t_map *map);

static int	check_owalls(char const *line)
{
	while (*line != '\n' && *line)
	{
		if (*(line++) != OBJ_WALL)
			return (0);
	}
	return (1);
}

static int	check_iwalls(char const *line)
{
	if (*line != OBJ_WALL)
		return (0);
	while (line[1] != '\n' && line[1])
		line++;
	if (*line != OBJ_WALL)
		return (0);
	return (1);
}

static int	check_object(char const *line, int *reqs)
{
	while (*line != '\n' && *line)
	{
		if (*line == OBJ_COLL)
			*reqs |= CHECK_COLL;
		else if (*line == OBJ_EXIT)
		{
			if (*reqs & CHECK_EXIT)
				return (0);
			*reqs |= CHECK_EXIT;
		}
		else if (*line == OBJ_STRT)
		{
			if (*reqs & CHECK_STRT)
				return (0);
			*reqs |= CHECK_STRT;
		}
	}
	return (*reqs & CHECK_COLL);
}

int	map_check(t_map *map)
{
	int		requirements;

	requirements = 0;
	if (!check_owalls((char *)map->content))
		return (0);
	map = map->next;
	while (map->next)
	{
		if (!check_iwalls((char *)map->content))
			return (0);
		map = map->next;
	}
	if (!check_owalls((char *)map->content))
		return (0);
	return (1);
}
