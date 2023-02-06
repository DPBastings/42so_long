/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:04:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/23 17:59:13 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include "libftprintf.h"

static int	check_slice(char const *slice, size_t len, int *reqs);

int	map_check_walls(t_map *map)
{
	char	*slice;
	size_t	is;
	size_t	io;

	is = 0;
	io = 0;
	slice = map->objs[is++];
	while (io < map->w)
	{
		if (slice[io++] != OBJ_WALL)
			return (0);
	}
	while (is < map->h)
	{
		slice = map->objs[is++];
		if (slice[0] != OBJ_WALL || slice[map->w - 1] != OBJ_WALL)
			return (0);
	}
	io = 0;
	while (io < map->w)
	{
		if (slice[io++] != OBJ_WALL)
			return (0);
	}
	return (1);
}

static int	check_slice(char const *slice, size_t len, int *reqs)
{
	while (len--)
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
		else if (!ft_strchr(OBJ_FILL, *slice))
			return (0);
		slice++;
	}
	return (1);
}

int	map_check_object(t_map *map)
{
	int		reqs;
	size_t	i;

	reqs = 0;
	i = 1;
	while (i < map->h - 1)
	{
		if (!check_slice(map->objs[i++], map->w - 1, &reqs))
			return (0);
	}
	return (reqs & CHECK_COLL);
}

int	map_check(t_map *map)
{
	if (map_check_walls(map) && map_check_object(map))
		return (map_check_path(map));
	return (0);
}
