/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_sprites_bind.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:00:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"

static int	sprite_bind(t_game *game, t_object *obj)
{
	t_sprite	*sprite;
	int			id;

	sprite = game->sprites[obj->type - 1];
	id = mlx_image_to_window(game->mlx, sprite->image,
			obj->position.x * GRID_W, obj->position.y * GRID_H);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	obj->sprite = sprite;
	return (id);
}

void	game_sprites_bind(t_game *game)
{
	t_point		p;
	t_object	**obj;

	p.y = 0;
	while (p.y < game->map->dims.h)
	{
		p.x = 0;
		while (p.x < game->map->dims.w)
		{
			obj = map_index(game->map, p);
			if (*obj)
				(*obj)->id = sprite_bind(game, *obj);
			p.x++;
		}
		p.y++;
	}
}
