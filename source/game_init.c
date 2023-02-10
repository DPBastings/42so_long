#include "so_long.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static mlx_t	*screen_init(unsigned int width, unsigned int height);
static void	game_abort(t_game *game, int errno);

t_game	*game_init(char const *filename)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		sl_error(SL_MEMFAIL);
	ft_printf("Loading map...\n");
	game->map = map_load(filename);
	if (!map_check(game->map))
		game_abort(game, SL_INVMAP);
	ft_printf("Establishing graphical environment...\n");
	game->mlx = screen_init(game->map->dims.w * GRID_W,	game->map->dims.h * GRID_H);
	if (game->mlx == NULL)
		game_abort(game, SL_MEMFAIL);
	ft_printf("Loading sprites...\n");
	game->sprites = sprites_load(game->mlx);
	if (game->sprites == NULL)
		game_abort(game, SL_MEMFAIL);
	ft_printf("Rendering...\n");
	game_sprites_bind(game);
	return (game);
}

static mlx_t	*screen_init(unsigned int width, unsigned int height)
{
	if (width < SCREEN_MIN_W)
		width = SCREEN_MIN_W;
	if (height < SCREEN_MIN_H)
		height = SCREEN_MIN_H;
	return (mlx_init(width, height, SL_TITLE, false));
}

static void	game_abort(t_game *game, int errno)
{
	game_end(game);
	sl_error(errno);
}

void	game_end(t_game *game)
{
	if (game == NULL)
		return ;
	mlx_terminate(game->mlx);
	ft_printf("Unloading sprites...\n");
	sprites_destroy(game->mlx, &game->sprites);
	ft_printf("Deallocating map...\n");
	map_destroy(&game->map);
	free(game);
	ft_printf("Goodbye!\n");
}
