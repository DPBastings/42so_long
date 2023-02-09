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
#include "map.h"
#include "libft.h"
#include <stdlib.h>

int	is_passable(t_object *obj)
{
	return (obj == NULL
		|| (obj->type != OBJ_WALL && obj->type != OBJ_NONE));
}

t_object	*object_init(unsigned int type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	return (new);
}

void	object_destroy(t_object **obj)
{
	free(*obj);
	*obj = NULL;
}

/* Return value corresponds to the object that previously occupied `newpos`
 * (either NULL or a passable object (i.e. a collectible).*/

//20230206 This is currently broken.
t_object	*object_move(t_object *obj, t_point newpos, t_map *map)
{
	t_object	*other;

	other = map->objs[newpos.y][newpos.x];
	if (is_passable(other))
	{
		map->objs[obj->position.y][obj->position.x] = NULL;
		map->objs[newpos.y][newpos.x] = obj;
		obj->position = newpos;
	}
	return (other);
}
