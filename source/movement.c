/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:28:07 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:10:15 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libftprintf.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdint.h>

void	object_move(t_object *obj)
{
	mlx_instance_t	*instance;

	instance = &obj->sprite->image->instances[obj->instance_id];
	instance_move(instance, obj->dir, obj->speed);
}

bool	object_align_grid(t_object *obj, t_map *map, t_view view)
{
	mlx_instance_t	instance;
	t_upoint		p;

	instance = obj->sprite->image->instances[obj->instance_id];
	set_upoint(&p,
		view_xgrid(instance.x, view),
		view_ygrid(instance.y, view));
	if (p.x % GRID_W == 0 && p.y % GRID_H == 0)
	{
		set_upoint(&p, p.x / GRID_W, p.y / GRID_H);
		object_place(obj, map, p);
		return (true);
	}
	return (false);
}

bool	player_move(t_game *game, t_dir dir)
{
	t_object	*player;
	t_object	**other;

	player = game->map->player;
	player->dir = dir;
	other = map_index(game->map, upoint_get_adjacent(player->position, dir));
	if (*other == game->map->none || !obj_is_passable(*other))
		return (false);
	sprite_change(player, game->sprites[SPR_PLYR_MOVE_UP + dir / 2], game);
	player->sprite->frame = 0;
	game->lock_input = true;
	player->speed = 6;
	game->moves++;
	hud_update_moves(game->hud, game->moves);
	ft_printf("Moves: %10u.\n", game->moves);
	return (true);
}

bool	enemy_move(t_object *enmy, t_game *game)
{	
	t_object	**other;

	other = map_index(game->map,
			upoint_get_adjacent(enmy->position, enmy->dir));
	if (*other && (*other)->type == OBJ_WALL)
		return (false);
	return (true);
}
