/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 17:49:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "geometry.h"
# include "libft.h"
# include "libftprintf.h"
# include "MLX42/MLX42.h"

# define GRID_SIZE		48
# define SL_FILEEXT		".ber"

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
	t_object	*none;
}	t_map;

# define NOWHERE	map->none

typedef struct s_game {
	t_map			*map;
	t_sprite		**sprites;
	unsigned int	score;
	unsigned int	moves;
}	t_game;

typedef enum e_sprites {
	WALL,
	COLL,
	EXIT,
	PLYR,
	N_SPRITES
}	t_sprites;

typedef enum e_sl_errno {
	SL_SUCCESS = 0,
	SL_MEMFAIL,
	SL_INVARGS,
	SL_INVEXT,
	SL_INVPATH,
	SL_INVMAP,
	N_SL_ERR,
}	t_sl_errno;

t_game		*game_init(mlx_t *mlx, char const *filename);
t_sprite	**sprites_load(mlx_t *mlx);
void		sprite_animate(t_sprite *sprite, unsigned int frame);
void		sprite_destroy(mlx_t *mlx, t_sprite **sprite);
t_object	*object_init(unsigned int type);
void		object_destroy(t_object **obj);
t_object	*object_move(t_object *obj, t_point newpos, t_map *map);
t_map		*map_load(char const *filename);
t_map		*map_init(t_plane dims);
void		map_set(t_map *map, t_list *bytemap);
void		map_destroy(t_map **map);

t_point		*get_adjacent(t_point p, t_map *map);
t_object	**map_index(t_map *map, t_point p);
int			is_passable(t_object *object);

void		sl_strerror(int errno);
void		sl_error(int errno);

# define TEXTURES_DIR	"./assets/textures/"
# define MAPS_DIR		"./assets/maps/"

#endif
