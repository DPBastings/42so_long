#include "so_long.h"
#include "MLX42/MLX42.h"

void	hook_close(void *param)
{
	t_game	*game;
	
	game = param;
	mlx_close_window(game->mlx);
}
