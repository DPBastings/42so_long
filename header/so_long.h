/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 16:31:09 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "geometry.h"
# include "libft.h"
# include "libftprintf.h"
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
# define SCREEN_MIN_W		384
# define SCREEN_MIN_H		240

# define SEC_PER_TICK		0.042

/* These values should be divisors of both GRID_W and GRID_H (if not, grid
 * alignment will no longer work properly."
 */
# define PLAYER_SPEED		6
# define ENEMY_SPEED		8

typedef enum e_objs {
	OBJ_NONE = 0,
	OBJ_PLYR,
	OBJ_COLL,
	OBJ_EXIT,
	OBJ_WALL,
	N_OBJS,
}	t_obj_id;

typedef enum e_textures {
	TXR_NONE = 0,
	TXR_PLYR,
	TXR_PLYR_IDLE,
	TXR_PLYR_WALK_U,
	TXR_PLYR_WALK_R,
	TXR_PLYR_WALK_D,
	TXR_PLYR_WALK_L,
	TXR_COLL,
	TXR_EXIT,
	//TXR_VORTEX,
	TXR_WALL,
	//TXR_RAINBOW,
	N_TEXTURES,
}	t_txr_id;

typedef enum e_sprites {
	SPR_NONE = 0,
	SPR_PLYR,
	SPR_PLYR_IDLE,
	SPR_PLYR_MOVE_UP,
	SPR_PLYR_MOVE_RIGHT,
	SPR_PLYR_MOVE_DOWN,
	SPR_PLYR_MOVE_LEFT,
	SPR_COLL_0,
	SPR_COLL_1,
	SPR_COLL_2,
	SPR_COLL_3,
	SPR_COLL_4,
	SPR_COLL_5,
	SPR_EXIT,
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
	//SPR_WALL_JUNC,
	N_SPRITES,
}	t_spr_id;

# define SPR_COLL_MAX		SPR_COLL_5
# define SPR_WALL_MAX		SPR_WALL_1111
# define N_COLL_SPR			(SPR_COLL_MAX - SPR_COLL_0 + 1)
# define N_WALL_SPR			(SPR_WALL_MAX - SPR_WALL_0000 + 1)

typedef enum e_dirs {
	DIR_UP = 0,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
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
	void 			(*animator)(struct s_sprite *, void *);
}	t_sprite;

typedef void (*t_spr_animator)(t_sprite *spr, void *param);

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
	t_point			position;
	bool			passable;
	bool			ticked;
	t_sprite		*sprite;
	int32_t			instance_id;
	struct s_object	*obj_below;
}	t_object;

typedef struct s_map {
	t_plane		dims;
	t_object	***objs;
	t_object	*player;
	t_object	*exit;
	t_object	*none;
}	t_map;

# define NOWHERE	map->none

typedef struct s_game {
	int32_t		seed;
	uint64_t	ticks;
	bool		lock_input;
	t_texture	**textures;
	t_texture	*gradient;
	t_sprite	**sprites;
	t_map		*map;
	t_point		draw_offset;
	uint32_t	score_max;
	uint32_t	score;
	uint32_t	moves;
	mlx_t		*mlx;
}	t_game;

typedef enum e_sl_errno {
	SL_SUCCESS = 0,
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
void		game_exit(t_game *game);
void		game_end(t_game *game);
int32_t		seed_get(t_game *game);

void		hook_set(t_game *game);
void		hook_close(void *param);
void		hook_keys(void *param);
bool		hook_keys_move(t_game *game);
void		hook_tick(void *param);

t_texture	**textures_load();
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
void		sprite_animate_move(t_sprite *spr, void *param);
bool		sprite_animation_is_done(t_sprite *spr);

typedef void (*t_spr_setter)(t_object *obj, t_game *game);
void		sprite_set_default(t_object *obj, t_game *game);
void		sprite_set_coll(t_object *obj, t_game *game);
void		sprite_set_wall(t_object *obj, t_game *game);

void		sprite_overlay_gradient(t_sprite *spr, mlx_texture_t *gradient);
uint8_t		*gradient_read(t_texture *gradient, uint32_t i);

t_object	*object_init(t_obj_id type);
bool		object_align_grid(t_object *obj, t_map *map);
t_object	**object_get_adjacent(t_object *obj, t_map *map, t_dir dir);
bool		object_is_passable(t_object *object);
void		object_move(t_object *obj, t_dir dir, uint16_t speed);
void		object_move_sprite(t_object *obj);
void		object_place(t_object *obj, t_map *map, t_point p);
void		object_destroy(t_object **obj);
bool		player_move(t_game *game, uint32_t dir);

typedef void (*t_obj_ticker)(t_object *obj, void *param);
void		objects_tick(t_game *game);
void		object_tick_default(t_object *obj, void *param);
void		object_tick_move(t_object *obj, void *param);
void		object_tick_coll(t_object *coll, void *param);
void		object_tick_enemy(t_object *enmy, void *param);
void		object_tick_exit(t_object *exit, void *param);
void		object_tick_player(t_object *plyr, void *param);

t_map		*map_load(char const *filename);
t_map		*map_init(t_plane dims);
bool		map_check(t_map *map);
uint32_t	map_get_maxscore(t_map *map);	
void		map_setup(t_map *map, t_list *bytemap);
t_object	**map_index(t_map *map, t_point p);
t_point		*map_get_adjacent(t_map *map, t_point p);
void		map_destroy(t_map **map);

t_point		point_get_adjacent(t_point p, uint32_t dir);

void		sl_strerror(t_sl_errno errno);
void		sl_error(t_sl_errno errno);

#endif
