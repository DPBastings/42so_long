/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:44:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	g_lookup_passable[N_OBJS] = {
	false,
	true,
	true,
	true,
	false,
};

/* t_object *object_init(unsigned int type)
 * Initializes a new object of type `type`.
 * Returns NULL on failure.
 */
t_object	*object_init(unsigned int type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	set_point(&new->position, -1, -1);
	new->facing = 0;
	new->moving = 0;
	new->passable = g_lookup_passable[type];
	new->sprite = NULL;
	new->instance_id = -1;
	new->obj_below = NULL;
	return (new);
}

/* int object_is_passable(t_object *obj)
 * Returns whether `obj` is passable.
 */
bool	object_is_passable(t_object *obj)
{
	return (obj == NULL || obj->passable);
}

void	object_destroy(t_object **obj)
{
	t_object	*below;

	if (*obj == NULL)
		return ;
	if ((*obj)->sprite)
		(*obj)->sprite->image->instances[(*obj)->instance_id].enabled = false;
	below = (*obj)->obj_below;
	free(*obj);
	*obj = below;
}
