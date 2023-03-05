/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick_coll.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 14:07:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 14:42:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>
#include <stdint.h>

#define AMPLITUDE 5

void	object_tick_coll(t_object *coll, void *param)
{
	mlx_instance_t	*instance;

	(void) param;
	//object_move_sprite(coll);
	instance = &coll->sprite->image->instances[coll->instance_id];
	if (instance->y <= (int32_t) coll->position.y * GRID_H - AMPLITUDE)
		coll->dir = DIR_DOWN;
	else if (instance->y >= (int32_t) coll->position.y * GRID_H + AMPLITUDE)
		coll->dir = DIR_UP;
}
