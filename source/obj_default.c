/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_default.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:02:32 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:01:55 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tick_default(t_object *obj, t_game *game)
{
	(void) game;
	obj->ticked = true;
}

bool	tick_move(t_object *obj, t_game *game)
{
	object_move(obj);
	return (object_align_grid(obj, game->map, game->view));
}
