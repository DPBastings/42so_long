/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charmap_general.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:11:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 12:09:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "charmap.h"
#include "libft.h"
#include <stdlib.h>

#include "libftprintf.h"

t_charmap	*charmap_copy(t_charmap *map)
{
	t_charmap	*copy;

	copy = ft_calloc(1, sizeof(t_charmap));
	if (copy == NULL)
		return (NULL);
	copy->objs = malloc(sizeof(char *) * map->dims.h);
	if (copy->objs == NULL)
		return (free(copy), NULL);
	copy->dims.h = 0;
	while (copy->dims.h < map->dims.h)
	{
		copy->objs[copy->dims.h] = ft_strdup(map->objs[copy->dims.h]);
		if (copy->objs[copy->dims.h] == NULL)
			return (charmap_destroy(&copy), NULL);
		copy->dims.h++;
	}
	copy->dims.w = map->dims.w;
	return (copy);
}

void	charmap_destroy(t_charmap **map)
{
	size_t	i;

	if (*map == NULL)
		return ;
	i = 0;
	while (i < (*map)->dims.h)
		free((*map)->objs[i++]);
	free((*map)->objs);
	free(*map);
	*map = NULL;
}
