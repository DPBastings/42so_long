/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 14:46:27 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "geometry.h"
# include "libft.h"
# include "libftprintf.h"
# include <limits.h>
# include "MLX42/MLX42.h"
# include <stdbool.h>
# include <stdint.h>

# include <stdio.h>

# define SL_TITLE			"Verve"
# define SL_FILEEXT			".ber"

# define SL_KEY_UP			MLX_KEY_W
# define SL_KEY_LEFT		MLX_KEY_A
# define SL_KEY_DOWN		MLX_KEY_S
# define SL_KEY_RIGHT		MLX_KEY_D

# define GRID_W				48
# define GRID_H				48
//SCREEN_W = (GRID_W * 26); SCREEN_H = (GRID_H * 15)
# define SCREEN_W			1248
# define SCREEN_H			720
# define HUD_W				1248
# define HUD_H				144
//VIEW_MAXW = SCREEN_W; VIEW_MAXH = (SCREEN_H - HUD_H)
# define VIEW_MAXW			1248
# define VIEW_MAXH			576

# define SEC_PER_TICK		0.042

/* These values should be divisors of both GRID_W and GRID_H (if not, grid
 * alignment will no longer work properly."
 */
# define PLAYER_SPEED		6

typedef enum e_objs {
	OBJ_NONE = 0,
	OBJ_PLYR,
	OBJ_COLL,
	OBJ_EXIT,
	OBJ_WALL,
	OBJ_ENMY_EASYH,
	OBJ_ENMY_EASYV,
	OBJ_ENMY_HARD,
	OBJ_ANIM,
	N_OBJS,
}	t_obj_id;

typedef enum e_textures {
	TXR_NONE = 0,
	TXR_GRADIENT,
	TXR_PLYR,
	TXR_PLYR_IDLE,
	TXR_PLYR_WALK_U,
	TXR_PLYR_WALK_R,
	TXR_PLYR_WALK_D,
	TXR_PLYR_WALK_L,
	TXR_ENMY_WALK_U,
	TXR_ENMY_WALK_R,
	TXR_ENMY_WALK_D,
	TXR_ENMY_WALK_L,
	TXR_COLL,
	TXR_EXIT,
	TXR_VORTEX,
	TXR_WALL,
	TXR_BG,
	TXR_HUD_BG,
	TXR_PROGRESS_BAR_FRAME,
	N_TEXTURES,
}	t_txr_id;

typedef enum e_sprites {
	SPR_NONE = 0,
	SPR_PLYR_IDLE,
	SPR_PLYR_MOVE_UP,
	SPR_PLYR_MOVE_RIGHT,
	SPR_PLYR_MOVE_DOWN,
	SPR_PLYR_MOVE_LEFT,
	SPR_ENMY_MOVE_UP,
	SPR_ENMY_MOVE_RIGHT,
	SPR_ENMY_MOVE_DOWN,
	SPR_ENMY_MOVE_LEFT,
	SPR_COLL_0,
	SPR_COLL_1,
	SPR_COLL_2,
	SPR_COLL_3,
	SPR_COLL_4,
	SPR_COLL_5,
	SPR_EXIT,
	SPR_VORTEX,
	SPR_WALL_0000,
	SPR_WALL_1000,
	SPR_WALL_0100,
	SPR_WALL_1100,
	SPR_WALL_0010,
	SPR_WALL_1010,
	SPR_WALL_0110,
	SPR_WALL_1110,
	SPR_WALL_0001,
	SPR_WALL_1001,
	SPR_WALL_0101,
	SPR_WALL_1101,
	SPR_WALL_0011,
	SPR_WALL_1011,
	SPR_WALL_0111,
	SPR_WALL_1111,
	SPR_WALL_JUNC,
	SPR_BG,
	N_SPRITES,
}	t_spr_id;

# define SPR_COLL_MAX		SPR_COLL_5 //15
# define SPR_WALL_MAX		SPR_WALL_1111 //33
# define N_COLL_SPR			(SPR_COLL_MAX - SPR_COLL_0 + 1) //5
# define N_WALL_SPR			(SPR_WALL_MAX - SPR_WALL_0000 + 1) //16
# define SPR_FILLER			SPR_WALL_0000 //18

typedef enum e_z {
	Z_BG0 = 0,
	Z_BG1,
	Z_MAP,
	Z_COLL0,
	Z_COLL1,
	Z_PLYR,
	Z_ENMY,
	Z_HUD0,
	Z_HUD1,
	Z_HUD2,
	Z_HUD3,
	Z_FG,
}	t_z;

typedef enum e_dirs {
	DIR_N = 0,
	DIR_NE,
	DIR_E,
	DIR_SE,
	DIR_S,
	DIR_SW,
	DIR_W,
	DIR_NW,
	N_DIRS,
}	t_dir;

typedef mlx_texture_t	t_texture;

/* Sprite object.
 * @param texture	The texture/spritesheet from which this sprite was created.
 * @param image		This sprite's image.
 * @param frame		The current animation frame.
 * @param frame_max	The maximum number of frames.
 * @param animator	The function used to animate this sprite.
 */
typedef struct s_sprite {
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	uint32_t		frame;
	uint32_t		frame_max;
	void			(*animator)(struct s_sprite *, void *);
}	t_sprite;

typedef void			(*t_spr_animator)(t_sprite *spr, void *param);

/* Object object.
 * @param type			The object's type.
 * @param position		The position of the object.
 * @param passable		Whether another object can move onto the same position as this object.
 * @param sprite		The object's sprite.
 * @param instance_id	The index of the sprite image instance corresponding to this object.
 * @param obj_below		A pointer to the object below this one at the same coordinate.
 */
typedef struct s_object {
	t_obj_id		type;
	uint16_t		dir;
	uint16_t		speed;
	t_upoint		position;
	int32_t			z;
	bool			passable;
	bool			ticked;
	t_sprite		*sprite;
	int32_t			instance_id;
	struct s_object	*above;
	struct s_object	*below;
}	t_object;

typedef struct s_map {
	t_upoint	dims;
	t_object	***objs;
	t_object	*player;
	t_object	*exit;
	t_object	*none;
}	t_map;

typedef struct s_view {
	t_point		origin;
	t_point		origin_max;
	t_point		port_min;
	t_point		port_max;
	mlx_image_t	*background;
}	t_view;

typedef struct s_bar {
	t_point		origin;
	double		filled;
	mlx_image_t	*bar;
	mlx_image_t	*mask;
	mlx_image_t	*frame;
}	t_bar;

typedef struct s_hud {
	mlx_image_t	*bg;
	mlx_image_t	*text;
	t_bar		*bar;
}	t_hud;

typedef struct s_game {
	int32_t		seed;
	uint64_t	ticks;
	bool		lock_input;
	t_texture	**textures;
	t_texture	*gradient;
	t_sprite	**sprites;
	t_hud		*hud;
	t_map		*map;
	uint32_t	score_max;
	uint32_t	score;
	uint32_t	moves;
	t_view		view;
	mlx_t		*mlx;
}	t_game;

typedef enum e_sl_errno {
	SL_SUCCESS = 0,
	SL_GENERIC,
	SL_MEMFAIL,
	SL_BADASS,
	SL_INVARGS,
	SL_INVEXT,
	SL_INVPATH,
	SL_INVMAP_DIMS,
	SL_INVMAP_UNKNOWNOBJ,
	SL_INVMAP_BOUNDS,
	SL_INVMAP_NOSTART,
	SL_INVMAP_NOEXIT,
	SL_INVMAP_EXCSTART,
	SL_INVMAP_EXCEXIT,
	SL_INVMAP_NOCOLL,
	SL_INVMAP_NOPATH,
	N_SL_ERR,
}	t_sl_errno;

t_game		*game_init(char const *filename);
void		object_collect(t_game *game, t_object **obj);
void		game_win(t_game *game);
void		game_lose(t_game *game);
void		game_exit(t_game *game);
void		game_end(t_game *game);
int32_t		seed_get(t_game *game);

void		hook_set(t_game *game);
void		hook_close(void *param);
void		hook_keys(void *param);
bool		hook_keys_move(t_game *game);
void		hook_tick(void *param);

void		textures_load(t_game *game);
t_texture	*texture_load(char const *filename);
void		textures_destroy(t_texture ***textures);
void		texture_destroy(t_texture **texture);

t_sprite	**sprites_init(t_game *game);
t_sprite	*sprite_new(t_game *game, unsigned int spr_id);
t_sprite	*sprite_load(t_texture *texture, mlx_t *mlx,
				unsigned int origin_i, unsigned int frame);
void		sprites_setup(t_game *game);
void		sprite_setup(t_object *obj, t_game *game);
void		sprite_change(t_object *obj, t_sprite *newspr, t_game *game);
void		sprites_destroy(t_sprite ***sprites, mlx_t *mlx);
void		sprite_destroy(t_sprite **sprite, mlx_t *mlx);

void		sprites_animate(t_game *game);
void		sprite_animate_pass(t_sprite *spr, void *param);
void		sprite_animate(t_sprite *spr, void *param);
void		sprite_animate_coll(t_sprite *spr, void *param);
void		sprite_animate_vortex(t_sprite *spr, void *param);
bool		sprite_animation_is_done(t_sprite *spr);

typedef void			(*t_spr_setter)(t_object *obj, t_game *game);
void		sprite_set_default(t_object *obj, t_game *game);
void		sprite_set_coll(t_object *obj, t_game *game);
void		sprite_set_enemy(t_object *obj, t_game *game);
void		sprite_set_wall(t_object *obj, t_game *game);

void		sprite_overlay_gradient(t_sprite *spr, mlx_texture_t *gradient);
void		image_overlay_gradient(mlx_image_t *img, mlx_texture_t *gradient,
			uint32_t i);
void		bar_overlay_gradient(mlx_image_t *bar, mlx_texture_t *gradient,
			uint32_t i);
uint8_t		*gradient_read(t_texture *gradient, uint32_t i);

t_object	*object_init(t_obj_id type);
bool		object_align_grid(t_object *obj, t_game *game);
t_object	**object_get_adjacent(t_object *obj, t_map *map, t_dir dir);
bool		object_is_passable(t_object *object);
void		object_move(t_object *obj);
void		object_place(t_object *obj, t_map *map, t_upoint p);
void		object_insert_above(t_object *obj, t_object *below);
void		object_insert_below(t_object *obj, t_object *above);
void		object_remove(t_object *obj, t_map *map);
void		object_destroy(t_object **obj);

bool		player_move(t_game *game, t_dir dir);
bool		enemy_move(t_object *enemy, t_game *game);
void		exit_open(t_object *exit, t_game *game);

typedef void			(*t_obj_ticker)(t_object *obj, t_game *game);
void		objects_tick(t_game *game);
bool		tick_move(t_object *obj, t_game *game);
void		tick_default(t_object *obj, t_game *game);
void		tick_coll(t_object *coll, t_game *game);
void		tick_enemy_easy(t_object *enemy, t_game *game);
void		tick_enemy_hard(t_object *enmy, t_game *game);
void		tick_exit(t_object *exit, t_game *game);
void		tick_player(t_object *plyr, t_game *game);

t_map		*map_load(char const *filename);
t_map		*map_init(t_upoint dims);
bool		map_check(t_map *map);
uint32_t	map_get_maxscore(t_map *map);	
void		map_setup(t_map *map, t_list *bytemap);
t_object	**map_index(t_map *map, t_upoint p);
void		map_destroy(t_map **map);

void		hud_init(t_game *game);
void		hud_bar_init(t_game *game, int32_t x, int32_t y);
void		hud_render(t_hud *hud, mlx_t *mlx);
void		hud_bar_animate(t_bar *bar, t_game *game);
void		hud_destroy(t_hud **hud, mlx_t *mlx);
void		hud_bar_destroy(t_bar **bar, mlx_t *mlx);
void		bg_render(t_game *game);
void		text_static_render(t_game *game);
void		text_dynamic_render(t_game *game);

void		view_init(t_game *game);
int32_t		view_xview(int32_t x, t_view view);
int32_t		view_yview(int32_t y, t_view view);
uint32_t	view_xgrid(int32_t x, t_view view);
uint32_t	view_ygrid(int32_t y, t_view view);
void		view_update(t_point diff, t_game *game);
void		view_centre(t_point anchor, t_game *game);
void		view_shift(t_point anchor, t_game *game);

t_dir		dir_invert(t_dir dir);
void		instance_move(mlx_instance_t *instance, t_dir dir, uint32_t speed);
t_point		instance_to_point(mlx_instance_t instance);
t_upoint	upoint_get_adjacent(t_upoint p, uint32_t dir);

void		sl_strerror(t_sl_errno errno);
void		sl_error(t_sl_errno errno);

#endif
