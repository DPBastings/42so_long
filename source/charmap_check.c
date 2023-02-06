/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charmap_check.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:04:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 15:25:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "charmap.h"
#include "libft.h"
#include "libftprintf.h"

static int	check_slice(char const *slice, size_t len, int *reqs);

int	charmap_check_walls(t_charmap *map)
{
	char	*slice;
	size_t	is;
	size_t	io;

	is = 0;
	io = 0;
	slice = map->objs[is++];
	while (io < map->dims.w)
	{
		if (slice[io++] != CHR_WALL)
			return (0);
	}
	while (is < map->dims.h)
	{
		slice = map->objs[is++];
		if (slice[0] != CHR_WALL || slice[map->dims.w - 1] != CHR_WALL)
			return (0);
	}
	io = 0;
	while (io < map->dims.w)
	{
		if (slice[io++] != CHR_WALL)
			return (0);
	}
	return (1);
}

static int	check_slice(char const *slice, size_t len, int *reqs)
{
	while (len--)
	{
		if (*slice == CHR_COLL)
			*reqs |= CHECK_COLL;
		else if (*slice == CHR_EXIT)
		{
			if (*reqs & CHECK_EXIT)
				return (0);
			*reqs |= CHECK_EXIT;
		}
		else if (*slice == CHR_STRT)
		{
			if (*reqs & CHECK_STRT)
				return (0);
			*reqs |= CHECK_STRT;
		}
		else if (!ft_strchr(CHR_FILL, *slice))
			return (0);
		slice++;
	}
	return (1);
}

int	charmap_check_object(t_charmap *map)
{
	int		reqs;
	size_t	i;

	reqs = 0;
	i = 1;
	while (i < map->dims.h - 1)
	{
		if (!check_slice(map->objs[i++], map->dims.w - 1, &reqs))
			return (0);
	}
	return (reqs & CHECK_COLL);
}

int	charmap_check(t_charmap *map)
{
	if (charmap_check_walls(map) && charmap_check_object(map))
		return (charmap_check_path(map));
	return (0);
}
