#include "so_long.h"
#include "MLX42/MLX42.h"
#include <math.h>

static void	hook_movement(t_game *game);
static void	hook_esc(t_game *game);

void	hook_keys(void *param)
{
	t_game	*game;

	game = param;
	if (!game->lock_input)
		hook_movement(game);
	hook_esc(game);
}

static void	hook_movement(t_game *game)
{
	static double	clock_playermove;
	double			now;
	t_object		*other;

	now = mlx_get_time();
	if (now - clock_playermove < 6 * INTV_ANIM_MOVE)
		return ;
	clock_playermove = now;
	other = game->NOWHERE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		other = object_move(game->map->player, game->map, 0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		other = object_move(game->map->player, game->map, 1, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		other = object_move(game->map->player, game->map, 0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		other = object_move(game->map->player, game->map, -1, 0);
	if (other == game->NOWHERE)
		return ;
	if (other && other->type == OBJ_COLL)
	{
		ft_printf("Fabelhaft!\n", other, other->type);
		object_destroy(&other);
		ft_printf("New score: %u! ", ++game->score);
	}
	ft_printf("You've made %u moves so far.\n", ++game->moves);
}

static void	hook_esc(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
