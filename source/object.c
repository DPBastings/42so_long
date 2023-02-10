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

t_object	*object_init(unsigned int type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->id = 0;
	return (new);
}

int	object_is_passable(t_object *obj)
{
	return (obj == NULL
		|| (obj->type != OBJ_WALL && obj->type != OBJ_NONE));
}

/* Return value corresponds to the object that previously occupied `newpos`
 * (either NULL or a passable object (i.e. a collectible).
 * 20230206 This is currently broken.
 */
t_object	*object_move(t_object *obj, t_point newpos, t_map *map)
{
	t_object	**other;

	other = map_index(map, newpos);
	if (object_is_passable(*other))
	{
		*map_index(map, obj->position) = NULL;
		*map_index(map, newpos) = obj;
		obj->position = newpos;
	}
	return (*other);
}

void	object_destroy(t_object **obj)
{
	free(*obj);
	*obj = NULL;
}
