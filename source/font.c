#include "so_long.h"

#include "MLX42/MLX42.h"

void	font_load(t_game *game)
{
	game->font = mlx_load_png("./assets/textures/font.png");
	if (game->font == NULL)
		sl_error(SL_MEMFAIL);
}
