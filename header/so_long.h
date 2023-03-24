/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 12:01:46 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "sl_general.h"
# include "sl_graphics.h"
# include "sl_hud.h"
# include "sl_object.h"
# include "sl_view.h"
# include "sl_utils.h"

# include "libft.h"
# include <limits.h>
# include "MLX42/MLX42.h"
# include "point.h"
# include <stdbool.h>
# include <stdint.h>

# define SL_TITLE			"Verve"

# define SL_KEY_UP			MLX_KEY_W
# define SL_KEY_LEFT		MLX_KEY_A
# define SL_KEY_DOWN		MLX_KEY_S
# define SL_KEY_RIGHT		MLX_KEY_D

/* These values should be divisors of both GRID_W and GRID_H (if not, grid
 * alignment will no longer work properly."
 */
# define PLAYER_SPEED		6

/* Game struct.
 * @param seed			A semi-random value, used to superficially randomize several
 * 						graphical game features.
 * @param ticks			The number of ticks elapsed.
 * @param lock_input	Whether player input (apart from ESC) is currently locked.
 * @param textures		Pointer to the texture array.
 * @param font			Pointer to the font texture.
 * @param sprites		Pointer to the sprite array.
 * @param hud			The game's heads-up display (HUD).
 * @param map			The game map.
 * @param score_max		The maximum score for this particular level.
 * @param score			Current score.
 * @param moves			Current number of moves.
 * @param view			The viewport.
 * @param mlx			Pointer to the MLX handle.
 */
typedef struct s_game {
	int32_t			seed;
	uint64_t		ticks;
	bool			lock_input;
	bool			game_over;
	mlx_texture_t	**textures;
	mlx_texture_t	*font;
	t_sprite		**sprites;
	t_hud			*hud;
	t_map			*map;
	uint32_t		score_max;
	uint32_t		score;
	uint32_t		moves;
	t_view			view;
	mlx_t			*mlx;
}	t_game;

t_game		*game_init(char const *filename);
void		object_collect(t_game *game, t_object **obj);
void		game_win(t_game *game);
void		game_lose(t_game *game);
void		game_end(t_game *game);
int32_t		seed_get(t_game *game);

void		hook_set(t_game *game);
void		hook_close(void *param);
void		hook_keys(void *param);
void		hook_tick(void *param);

void		sprites_setup(t_game *game);
void		sprite_setup(t_object *obj, t_game *game);
void		sprite_change(t_object *obj, t_sprite *newspr, t_game *game);

void		sprites_animate(t_game *game);

bool		player_move(t_game *game, t_dir dir);
bool		enemy_move(t_object *enemy, t_game *game);
void		exit_open(t_object *exit, t_game *game);

typedef void			(*t_obj_ticker)(t_object *obj, t_game *game);
void		objects_tick(t_game *game);
bool		tick_move(t_object *obj, t_game *game);
void		tick_default(t_object *obj, t_game *game);
void		tick_coll(t_object *coll, t_game *game);
void		tick_enemy(t_object *enemy, t_game *game);
void		tick_exit(t_object *exit, t_game *game);
void		tick_player(t_object *player, t_game *game);

bool		object_align_grid(t_object *obj, t_map *map, t_view view);
void		bg_render(t_game *game);
void		hud_bar_animate(t_bar *bar, t_game *game);

#endif
