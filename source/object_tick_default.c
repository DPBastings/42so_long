/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick_default.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:02:32 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 16:19:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	object_tick_default(t_object *obj, void *param)
{
	(void) param;
	obj->ticked = true;
}

void	object_tick_move(t_object *obj, void *param)
{
	t_game	*game;

	game = param;
	object_move_sprite(obj);
	object_align_grid(obj, game);
}
