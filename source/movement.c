/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:28:07 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:52:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdint.h>

bool	player_move(t_game *game, t_dir dir)
{
	t_object	*player;
	t_object	**other;

	player = game->map->player;
	player->dir = dir;
	other = map_index(game->map, upoint_get_adjacent(player->position, dir));
	if (*other == game->map->none || !object_is_passable(*other))
		return (false);
	sprite_change(player, game->sprites[SPR_PLYR_MOVE_UP + dir], game);
	player->sprite->frame = 0;
	game->lock_input = true;
	player->speed = PLAYER_SPEED;
	game->moves++;
	ft_printf("Moves: [%u].\n", game->moves);
	return (true);
}

bool	enemy_move(t_object *enmy, t_game *game)
{	
	t_object	**other;
	
	other = map_index(game->map, upoint_get_adjacent(enmy->position, enmy->dir));
	if (*other && ((*other)->type == OBJ_WALL || (*other)->type == OBJ_WALL))
		return (false);
	return (true);
}
