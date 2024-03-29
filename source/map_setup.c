/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_setup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:45:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 14:01:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"
#include "sl_map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static t_obj_id	chrtotype(char const chr);
static void		object_setup(t_map *map, t_upoint p, char type);

void	map_setup(t_map *map, t_list *bytemap)
{
	t_upoint	p;
	char		*row;

	p.y = 0;
	while (p.y < map->dims.y)
	{
		p.x = 0;
		row = (char *)bytemap->content;
		while (p.x < map->dims.x)
		{
			if (row[p.x] != CHR_NONE)
				object_setup(map, p, row[p.x]);
			p.x++;
		}
		bytemap = bytemap->next;
		p.y++;
	}
}

static void	object_setup(t_map *map, t_upoint p, char type)
{
	t_object	*obj;

	obj = object_init(chrtotype(type));
	obj->below = map->none;
	object_place(obj, map, p);
	if (obj->type == OBJ_PLYR)
		map->player = obj;
	else if (obj->type == OBJ_EXIT)
		map->exit = obj;
}

static t_obj_id	chrtotype(char const chr)
{
	char *const	chars = CHR_ALL;
	char		*ptr;

	ptr = ft_strchr(chars, chr);
	if (ptr == NULL)
		sl_error(SL_INVMAP_UNKNOWNOBJ);
	return ((t_obj_id)(ptr - chars));
}
