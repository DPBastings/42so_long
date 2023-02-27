/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   seed.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:28:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 14:46:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdint.h>

int32_t	seed_get(t_game *game)
{
	int32_t	a;
	int32_t	b;
	int32_t	c;
	int32_t	d;

	a = game->map->dims.h * game->map->dims.w;
	b = game->map->player->position.x * game->map->player->position.y;
	c = (int32_t) game->score_max;
	d = (int32_t) game->mlx;
	return (d / (a - b + c) * (d % (a + c)));
}
