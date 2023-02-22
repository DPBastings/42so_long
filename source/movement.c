/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:28:07 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 13:18:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdint.h>

t_point	point_get_adjacent(t_point p, uint32_t dir);

bool	player_move(t_game *game, uint32_t dir)
{
	t_object	*player;
	t_object	**other;

	player = game->map->player;
	player->facing = dir;
	other = map_index(game->map, point_get_adjacent(player->position, dir));
	if (*other == game->NOWHERE || !object_is_passable(*other))
		return (false);
	sprite_change(player, game->sprites[SPR_PLYR_MOVE_UP + dir], game);
	player->sprite->frame = 0;
	game->lock_input = true;
	object_move(player, dir, 1);
	game->moves++;
	ft_printf("Moves: [%u].\n", game->moves);
	return (true);
}
