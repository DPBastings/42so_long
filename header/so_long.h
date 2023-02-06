/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/27 14:38:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include <stddef.h>

# define GRID_SIZE		48

typedef struct s_game {
	t_tilemap		*map;
	unsigned int	score;
	unsigned int	moves;
}	t_game;

typedef struct s_sprite {
	mlx_texture_t	*texture;
	mlx_image_t		*image;
}	t_sprite;

typedef struct s_tile {
	t_point			position;
	t_sprite		*sprite;
	unsigned int	id;
}	t_tile;

typedef struct s_tilemap {
	t_plane		dims;
	t_tile		**tiles;
}	t_tilemap;

typedef enum e_sprites {
	WALL,
	BACH,
	SCORE,
	EXIT,
	N_SPRITES
}	t_sprites;

# define TEXTURES_DIR	"./assets/textures/"
# define MAPS_DIR		"./assets/maps/"

#endif
