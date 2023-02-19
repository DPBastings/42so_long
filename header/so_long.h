/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:43:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "geometry.h"
# include "libft.h"
# include "libftprintf.h"
# include "MLX42/MLX42.h"
# include <stdint.h>

# include <stdio.h>

# define SL_TITLE			"The Bach Game"
# define SL_FILEEXT			".ber"

# define SL_KEY_UP			MLX_KEY_W
# define SL_KEY_LEFT		MLX_KEY_A
# define SL_KEY_DOWN		MLX_KEY_S
# define SL_KEY_RIGHT		MLX_KEY_D

# define GRID_W				48
# define GRID_H				48
# define SCREEN_MIN_W		1152
# define SCREEN_MIN_H		864

# define SEC_PER_TICK		0.05
# define TICKS_PER_ANIM_FG	2
# define INTV_ANIM_MOVE		0.04
# define INTV_ANIM_BG		0.10

typedef enum e_objs {
	OBJ_NONE = 0,
	OBJ_PLYR,
	OBJ_COLL,
	OBJ_EXIT,
	OBJ_WALL,
	N_OBJS,
}	t_obj_ids;

typedef enum e_textures {
	TXR_NONE = 0,
	TXR_PLYR,
	TXR_COLL,
	TXR_EXIT,
	TXR_WALL,
	N_TEXTURES,
}	t_texture_ids;

typedef enum e_sprites {
	SPR_NONE = 0,
	SPR_PLYR,
	SPR_COLL_0,
	SPR_COLL_1,
	SPR_COLL_2,
	SPR_COLL_3,
	SPR_COLL_4,
	SPR_COLL_5,
	SPR_EXIT,
	SPR_WALL_1111,
	N_SPRITES,
}	t_sprite_ids;

# define SPR_COLL_MAX		SPR_COLL_5

typedef enum e_dirs {
	DIR_UP = 0,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	N_DIRS,
}	t_dir_ids;

typedef struct s_texture {
	mlx_texture_t	*texture;
	mlx_texture_t	*gradient;
}	t_texture;

typedef struct s_sprite {
	mlx_image_t		*image;
	unsigned int	frame;
	mlx_t			*mlx;
}	t_sprite;

typedef struct s_object {
	t_point			position;
	unsigned int	type;
	int				instance_id;
	t_sprite		*sprite;
}	t_object;

typedef struct s_map {
	t_plane		dims;
	t_object	***objs;
	t_object	*player;
	t_object	*none;
}	t_map;

# define NOWHERE	map->none

typedef struct s_game {
	size_t			ticks;
	int				lock_input;
	t_texture		**textures;
	mlx_texture_t	*gradient;
	t_sprite		**sprites;
	t_map			*map;
	unsigned int	score_max;
	unsigned int	score;
	unsigned int	moves;
	mlx_t			*mlx;
}	t_game;

typedef enum e_sl_errno {
	SL_SUCCESS = 0,
	SL_MEMFAIL,
	SL_BADASS,
	SL_INVARGS,
	SL_INVEXT,
	SL_INVPATH,
	SL_INVMAP,
	N_SL_ERR,
}	t_sl_errno;

typedef unsigned int (*t_sprite_shifter)(t_object *obj, void *param);

t_game		*game_init(char const *filename);
void		object_collect(t_game *game, t_object **obj);
void		game_exit(t_game *game);
void		game_end(t_game *game);

void		hook_set(t_game *game);
void		hook_close(void *param);
void		hook_keys(void *param);
void		hook_tick(void *param);

t_texture	**textures_load(t_game *game);
t_texture	*texture_load(char const *filename);
void		textures_destroy(t_texture ***textures);
void		texture_destroy(t_texture **texture);

t_sprite	**sprites_init(t_game *game);
t_sprite	*sprite_new(t_game *game, unsigned int spr_id);
t_sprite	*sprite_load(t_texture *texture, mlx_t *mlx,
			unsigned int origin_i, unsigned int frame);
void		sprites_destroy(t_sprite ***sprites);
void		sprite_destroy(t_sprite **sprite);
void		sprites_bind(t_game *game);
void		sprite_bind(t_object *obj, t_game *game);

void		sprite_animate(t_sprite *sprite);
void		sprite_animate_coll(t_sprite *sprite, t_game *game);
void		sprite_overlay_gradient(t_sprite *sprite, mlx_texture_t *gradient);
unsigned	sprite_shift_coll(t_object *obj, void *param);
unsigned	sprite_shift_wall(t_object *obj, void *param);

uint8_t		*gradient_read(mlx_texture_t *gradient, uint32_t i);

t_object	*object_init(unsigned int type);
t_object	*object_move(t_object *obj, t_map *map,
			uint32_t xdelta, uint32_t ydelta);
int			player_move(t_game *game, uint32_t xdelta, uint32_t ydelta);
int			object_is_passable(t_object *object);
void		object_destroy(t_object **obj);

t_map		*map_load(char const *filename);
t_map		*map_init(t_plane dims);
int			map_check(t_map *map);
uint32_t	map_get_maxscore(t_map *map);	
void		map_set(t_map *map, t_list *bytemap);
t_object	**map_index(t_map *map, t_point p);
t_point		*map_get_adjacent(t_map *map, t_point p);
void		map_destroy(t_map **map);

void		sl_strerror(int errno);
void		sl_error(int errno);

#endif
