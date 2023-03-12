/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_coll.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 14:07:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:45:55 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>
#include <stdint.h>

#define AMPLITUDE 5

void	tick_coll(t_object *coll, void *param)
{
	int32_t			y;
	int32_t			zero;
	t_view			view;

	view = ((t_game *)param)->view;
	object_move_sprite(coll);
	y = coll->sprite->image->instances[coll->instance_id].y;
	zero = view_yview((int32_t) coll->position.y * GRID_H, view);
	if (y <= zero - AMPLITUDE)
		coll->dir = DIR_DOWN;
	else if (y >= zero + AMPLITUDE)
		coll->dir = DIR_UP;
}
