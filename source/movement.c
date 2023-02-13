/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:28:07 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 16:50:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

int	player_move(t_game *game, uint32_t xdelta, uint32_t ydelta)
{
	t_object	*other;

	other = object_move(game->map->player, game->map, xdelta, ydelta);
	if (other == game->NOWHERE)
		return (0);
	if (other && other->type == OBJ_COLL)
	{
		object_destroy(&other);
		ft_printf("New score: %u! ", ++game->score);
	}
	ft_printf("You've made %u moves so far.\n", ++game->moves);
	return (1);
}
