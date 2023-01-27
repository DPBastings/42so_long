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

t_map	*map_copy(t_map *map)
{
	t_map	*copy;
	size_t	i;
	
	copy = ft_calloc(sizeof(t_map));
	if (copy == NULL)
		return (NULL);
	copy->objs = malloc(sizeof(char*) * map->h);
	if (copy->objs == NULL)
		return (free(copy), NULL);
	i = 0;
	while (i < map->h)
	{
		copy->objs[i] = ft_strdup(map->objs[i]);
		if (copy->objs[i] == NULL)
			return (map_destroy(&copy), NULL);
		i++;
	}
	copy->w = map->w;
	copy->h = map->h;
	return (copy);
}

void	map_destroy(t_map **map)
{
	char	**tmp;

	tmp = (*map)->objs;
	while (tmp)
	{
		free(*tmp);
		tmp++;
	}
	free((*map)->objs);
	free(*map);
	*map = NULL;
}
