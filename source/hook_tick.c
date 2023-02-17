/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_tick.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 16:50:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"
#include <math.h>

static void	sprites_animate(t_game *game);

void	hook_tick(void *param)
{
	t_game	*game;

	game = param;
	sprites_animate(game);
}

static void	sprites_animate(t_game *game)
{
	unsigned int	id;

	id = SPR_COLL_0;
	while (id < SPR_COLL_3)
	{
		sprite_overlay_gradient(game->sprites[id], game->gradient);
		game->sprites[id]->frame++;
		id++;
	}
}
