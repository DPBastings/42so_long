#include "so_long.h"

#include "geometry.h"

static void	draw_bg_element(t_point p, t_game *game);

void	draw_bg(t_game *game)
{
	t_point	p;
	int32_t	xstart;
	
	p.y = HUD_H - (game->view.offset.y % GRID_H);
	printf("%u\n", game->view.offset.y);
	xstart = -(game->view.offset.x % GRID_W);
	while (p.y < SCREEN_H)
	{
		p.x = xstart;
		while (p.x < SCREEN_W)
		{
			draw_bg_element(p, game);
			p.x += GRID_W;
		}
		p.y += GRID_H;
	}
}

static void	draw_bg_element(t_point p, t_game *game)
{
	mlx_image_t	*fill;
	mlx_image_t	*bg;
	int32_t		id;

	fill = game->sprites[SPR_FILLER]->image;
	bg = game->sprites[SPR_BG]->image;
	if (p.x >= game->view.offset.x
			&& p.x < SCREEN_W - game->view.offset.x
			&& p.y >= game->view.offset.y
			&& p.y < SCREEN_H - (game->view.offset.y - HUD_H))
	{
		id = mlx_image_to_window(game->mlx, bg, p.x, p.y);
		if (id == -1)
			sl_error(SL_MEMFAIL);
		mlx_set_instance_depth(&bg->instances[id], -1);
	}
	else
	{
		id = mlx_image_to_window(game->mlx, fill, p.x, p.y);
		if (id == -1)
			sl_error(SL_MEMFAIL);
		mlx_set_instance_depth(&fill->instances[id], 0);
	}
}
