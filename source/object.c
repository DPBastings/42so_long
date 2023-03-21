/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:12:11 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"

#include "point.h"
#include "libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

enum e_obj_vars {
	OBJ_Z	= 0,
	OBJ_DIR,
	OBJ_SPEED,
	OBJ_PASSABLE,
	N_OBJ_VARS,
};

static int32_t	g_lut_obj_vars[N_OBJS][N_OBJ_VARS] = {
{Z_FG,		DIR_N,	0,	false,},
{Z_PLYR,	DIR_S,	0,	true,},
{Z_COLL0,	DIR_N,	1,	true,},
{Z_MAP,		DIR_N,	0,	true,},
{Z_MAP,		DIR_N,	0,	false,},
{Z_ENMY,	DIR_E,	6,	true,},
{Z_ENMY,	DIR_S,	6,	true,},
{Z_BG1,		DIR_N,	0,	true,},};

t_object	*object_init(t_obj_id type)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (obj == NULL)
		sl_error(SL_MEMFAIL);
	obj->type = type;
	set_upoint(&obj->position, -1, -1);
	obj->z = g_lut_obj_vars[type][OBJ_Z];
	obj->dir = g_lut_obj_vars[type][OBJ_DIR];
	obj->speed = g_lut_obj_vars[type][OBJ_SPEED];
	obj->passable = g_lut_obj_vars[type][OBJ_PASSABLE];
	obj->sprite = NULL;
	obj->instance_id = -1;
	obj->above = NULL;
	obj->below = NULL;
	return (obj);
}

bool	obj_is_passable(t_object *obj)
{
	return (obj == NULL || obj->passable);
}

bool	obj_is_harmful(t_object *obj)
{
	return (obj && (obj->type == OBJ_ENMY_H || obj->type == OBJ_ENMY_V));
}

void	object_destroy(t_object **obj)
{
	t_object	*below;

	if (*obj == NULL)
		return ;
	if ((*obj)->sprite)
		(*obj)->sprite->image->instances[(*obj)->instance_id].enabled = false;
	below = (*obj)->below;
	if (below)
		below->above = (*obj)->above;
	free(*obj);
	*obj = below;
}
