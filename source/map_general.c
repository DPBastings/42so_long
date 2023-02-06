/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_general.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:11:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/27 16:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include <stdlib.h>

#include "libftprintf.h"

t_map	*map_copy(t_map *map)
{
	t_map	*copy;

	copy = ft_calloc(1, sizeof(t_map));
	if (copy == NULL)
		return (NULL);
	copy->objs = malloc(sizeof(char *) * map->h);
	if (copy->objs == NULL)
		return (free(copy), NULL);
	copy->h = 0;
	while (copy->h < map->h)
	{
		copy->objs[copy->h] = ft_strdup(map->objs[copy->h]);
		if (copy->objs[copy->h] == NULL)
			return (map_destroy(&copy), NULL);
		copy->h++;
	}
	copy->w = map->w;
	return (copy);
}

void	map_destroy(t_map **map)
{
	size_t	i;

	if (*map == NULL)
		return ;
	i = 0;
	while (i < (*map)->h)
		free((*map)->objs[i++]);
	free((*map)->objs);
	free(*map);
	*map = NULL;
}
