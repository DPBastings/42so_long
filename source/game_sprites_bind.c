#include "so_long.h"
#include "MLX42/MLX42.h"

void	game_sprites_bind(t_game *game)
{
	t_point		p;
	t_object	**obj;
	int			id;

	p.y = 0;
	while (p.y < game->map->dims.h)
	{
		p.x = 0;
		while (p.x < game->map->dims.w)
		{
			obj = map_index(game->map, p);
			if (*obj)
			{
				id = mlx_image_to_window(game->mlx,
					game->sprites[(*obj)->type - 1]->image,
					(*obj)->position.x * GRID_W,
					(*obj)->position.y * GRID_H);
				if (id == -1)
					sl_error(SL_MEMFAIL);
				(*obj)->id = id;
			}
			p.x++;
		}
		p.y++;
	}
}
