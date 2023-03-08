#include "so_long.h"

#include "geometry.h"
#include "ft_math.h"

static void	apply_offset(t_view *view);

static void	print_view(t_view view)
{
	printf("|SCREEN:     %4d %4d\n", SCREEN_W, SCREEN_H);
	printf("|origin_max: %4d %4d\n", view.origin_max.x, view.origin_max.y);
	printf("|port_min:   %4d %4d\n", view.port_min.x, view.port_min.y);
	printf("|port_max:   %4d %4d\n", view.port_max.x, view.port_max.y);
}

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
	game->view.port_max.y = VIEW_MAXH - game->view.port_min.y;
	game->view.origin_max.x = ft_intmax(2, 0, pixel_dims.x - game->view.port_max.x);
	game->view.origin_max.y = ft_intmax(2, 0, pixel_dims.y - game->view.port_max.y);
	apply_offset(&game->view);
}

static void	apply_offset(t_view *view)
{
	view->port_min.y += HUD_H;
	view->port_max.y += HUD_H;
}
