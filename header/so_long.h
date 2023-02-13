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

# define INTV_ANIM_MOVE		0.04
# define INTV_ANIM_BG		0.10

typedef enum e_objs {
	OBJ_NONE = 0,
	OBJ_WALL,
	OBJ_COLL,
	OBJ_EXIT,
	OBJ_PLYR,
	OBJ_ENMYH,
	OBJ_ENMYV,
	N_OBJS,
}	t_objs;

typedef enum e_dirs {
	DIR_UP = 0,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	N_DIRS,
}	t_dirs;

typedef struct s_sprite {
	mlx_texture_t	*texture;
	mlx_image_t		*image;
}	t_sprite;

typedef struct s_object {
	t_point			position;
	unsigned int	type;
	unsigned int	id;
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
	mlx_t			*mlx;
	t_map			*map;
	t_sprite		**sprites;
	unsigned int	score;
	unsigned int	total_score;
	unsigned int	moves;
	int				lock_input;
}	t_game;

typedef enum e_sprites {
	SPR_WALL,
	SPR_COLL,
	SPR_EXIT,
	SPR_PLYR,
	N_SPRITES,
}	t_sprites;

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

t_game		*game_init(char const *filename);
void		game_sprites_bind(t_game *game);
void		object_collect(t_game *game, t_object **obj);
void		game_exit(t_game *game);
void		game_end(t_game *game);

void		hook_set(t_game *game);
void		hook_keys(void *param);
void		hook_close(void *param);

t_sprite	**sprites_load(mlx_t *mlx);
t_sprite	*sprite_load(mlx_t *mlx, char const *filename);
void		sprite_animate(t_sprite *sprite, unsigned int frame);
void		sprite_destroy(mlx_t *mlx, t_sprite **sprite);
void		sprites_destroy(mlx_t *mlx, t_sprite ***sprites);

t_object	*object_init(unsigned int type);
t_object	*object_move(t_object *obj, t_map *map, 
			uint32_t xdelta, uint32_t ydelta);
int			player_move(t_game *game, uint32_t xdelta, uint32_t ydelta);
int			object_is_passable(t_object *object);
void		object_destroy(t_object **obj);

t_map		*map_load(char const *filename);
t_map		*map_init(t_plane dims);
int			map_check(t_map *map);
uint32_t	map_get_total_score(t_map *map);	
void		map_set(t_map *map, t_list *bytemap);
t_object	**map_index(t_map *map, t_point p);
t_point		*map_get_adjacent(t_map *map, t_point p);
void		map_destroy(t_map **map);

void		sl_strerror(int errno);
void		sl_error(int errno);

#endif
