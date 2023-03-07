#include "so_long.h"

#include "geometry.h"
#include "ft_math.h"

static void	apply_offset(t_view *view);

void	view_init(t_game *game)
{	
	t_upoint	pixel_dims;

	pixel_dims.x = game->map->dims.x * GRID_W;
	pixel_dims.y = game->map->dims.y * GRID_H;
	if (pixel_dims.x < VIEW_MAXW)
		game->view.port_min.x = (VIEW_MAXW - pixel_dims.x) / 2;
	if (pixel_dims.y < VIEW_MAXH)
		game->view.port_min.y = (VIEW_MAXH - pixel_dims.y) / 2;
	game->view.port_max.x = VIEW_MAXW - game->view.port_min.x;
	game->view.port_max.y = SCREEN_H - game->view.port_min.y;
	game->view.origin_max.x = ft_intmax(2, 0, pixel_dims.x - game->view.port_max.x);
	game->view.origin_max.y = ft_intmax(2, 0, pixel_dims.y - game->view.port_max.y);
	game->view.port_size.x = game->view.port_max.x + game->view.port_min.x;
	game->view.port_size.y = game->view.port_max.y + game->view.port_min.y;
	apply_offset(&game->view);
	printf("|screen:     %4i %4i\n|origin_max: %4d %4d\n|port_min:   %4d %4d\n|port_max:   %4d %4d\n",
			SCREEN_W, SCREEN_H,
			game->view.origin_max.x, game->view.origin_max.y,
			game->view.port_min.x, game->view.port_min.y,
			game->view.port_max.x, game->view.port_max.y);
}

static void	apply_offset(t_view *view)
{
	view->port_min.y += HUD_H;
	view->origin_max.y += HUD_H;
}
