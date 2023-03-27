/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_graphics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 13:54:10 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_GRAPHICS_H
# define SL_GRAPHICS_H

# include "MLX42/MLX42.h"
# include <stdint.h>

typedef enum e_textures {
	TXR_NONE = 0,
	TXR_GRADIENT,
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
	TXR_LOGO,
	TXR_PROGRESS_BAR,
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
	SPR_WALL_00000000,
	SPR_WALL_00000001,
	SPR_WALL_00000100,
	SPR_WALL_00000101,
	SPR_WALL_00010000,
	SPR_WALL_00010001,
	SPR_WALL_00010100,
	SPR_WALL_00010101,
	SPR_WALL_01000000,
	SPR_WALL_01000001,
	SPR_WALL_01000100,
	SPR_WALL_01000101,
	SPR_WALL_01010000,
	SPR_WALL_01010001,
	SPR_WALL_01010100,
	SPR_WALL_01010101,
	SPR_WALL_JUNC,
	SPR_WALL_00000010,
	SPR_WALL_00001000,
	SPR_WALL_00001010,
	SPR_WALL_00100000,
	SPR_WALL_00100010,
	SPR_WALL_00101000,
	SPR_WALL_00101010,
	SPR_WALL_10000000,
	SPR_WALL_10000010,
	SPR_WALL_10001000,
	SPR_WALL_10001010,
	SPR_WALL_10100000,
	SPR_WALL_10100010,
	SPR_WALL_10101000,
	SPR_WALL_10101010,
	SPR_BG,
	N_SPRITES,
}	t_spr_id;

# define SPR_COLL_MIN		10	// SPR_COLL_0
# define SPR_COLL_MAX		15	// SPR_COLL_5
# define SPR_WALL_MIN		18	// SPR_WALL_00000000
# define SPR_WALL_MAX		49	// SPR_WALL_10101010
# define N_COLL_SPR			5	// (SPR_COLL_MAX - SPR_COLL_MIN + 1)
# define N_WALL_SPR			32	// (SPR_WALL_MAX - SPR_WALL_MIN + 1)
# define SPR_FILLER			18	// SPR_WALL_00000000

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

mlx_texture_t	**textures_load(void);
mlx_texture_t	*texture_load(char const *filename);
void			textures_destroy(mlx_texture_t ***textures);

t_sprite		**sprites_init(mlx_t *mlx, mlx_texture_t **txrs);
void			sprites_destroy(t_sprite ***sprites, mlx_t *mlx);

void			sprite_animate_pass(t_sprite *spr, void *param);
void			sprite_animate(t_sprite *spr, void *param);
void			sprite_animate_coll(t_sprite *spr, void *param);
void			sprite_animate_vortex(t_sprite *spr, void *param);
bool			sprite_animation_is_done(t_sprite *spr);

void			sprite_hueshift(t_sprite *spr, mlx_texture_t *gradient);
void			image_hueshift(mlx_image_t *img, mlx_texture_t *gradient,
					uint32_t frame);
void			texture_hueshift(mlx_texture_t *txr, mlx_texture_t *gradient,
					uint32_t frame);
void			bar_hueshift(mlx_image_t *bar,
					mlx_texture_t *gradient, uint32_t i);
void			textures_plyr_hueshift(mlx_texture_t **txrs, uint32_t frame);
uint8_t			*gradient_read(mlx_texture_t *gradient, uint32_t i);

#endif
