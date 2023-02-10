#include "so_long.h"
#include "MLX42/MLX42.h"

void	hook_set(t_game *game)
{
	mlx_loop_hook(game->mlx, hook_keys, game);
	mlx_close_hook(game->mlx, hook_close, game);
}
