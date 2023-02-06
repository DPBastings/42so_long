/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 18:11:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <stdlib.h>

static unsigned int	gettype(char type)
{
	char *const	chars = CHR_ALL;
	char		*ptr;

	ptr = ft_strchr(chars, type);
	if (ptr == NULL)
		return (OBJ_NONE);
	return ((unsigned int)(ptr - chars));
}

static int	is_passable(t_object *obj)
{
	return (obj == NULL || obj->type == OBJ_COLL);
}

t_object	*object_init(char type)
{
	t_object	*new;

	if (type == CHR_NONE)
		return (NULL);
	new = malloc(sizeof(t_object));
	if (new == NULL)
		sl_error(SL_MEMFAIL);
	new->type = gettype(type);
	return (new);
}

void	object_destroy(t_object **obj)
{
	free(*obj);
	*obj = NULL;
}

/* Return value corresponds to the object that previously occupied `newpos`
 * (either NULL or a passable object (i.e. a collectible).*/

//20220206 This is currently broken.
t_object	*object_move(t_object *obj, t_point newpos, t_tilemap *map)
{
	t_object	*other;

	other = map->tiles[newpos.y][newpos.x];
	if (is_passable(other))
	{
		map->tiles[obj->position.y][obj->position.x] = NULL;
		map->tiles[newpos.y][newpos.x] = obj;
		obj->position = newpos;
	}
	return (other);
}
