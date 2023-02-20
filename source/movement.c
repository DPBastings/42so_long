/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:28:07 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 12:54:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdint.h>

bool	player_move(t_game *game, uint32_t xdelta, uint32_t ydelta)
{
	t_object	*other;

	other = object_move(game->map->player, game->map, xdelta, ydelta);
	if (other == game->NOWHERE)
		return (false);
	if (other)
	{
		if (other->type == OBJ_COLL)
			object_collect(game, &other);
		else if (other->type == OBJ_EXIT && game->score >= game->score_max)
		{
			game_exit(game);
			return (true);
		}
		else
			game->map->player->obj_below = other;
	}
	game->moves++;
	ft_printf("Moves: [%u].\n", game->moves);
	return (true);
}
