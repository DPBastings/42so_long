/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_graphics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 16:46:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_GRAPHICS_H
# define SL_GRAPHICS_H

# include "MLX42/MLX42.h"
# include "point.h"
# include <stdint.h>

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

# define SPR_COLL_MAX		15	// SPR_COLL_5
# define SPR_WALL_MAX		33	// SPR_WALL_1111
# define N_COLL_SPR			5	// (SPR_COLL_MAX - SPR_COLL_0 + 1)
# define N_WALL_SPR			16	// (SPR_WALL_MAX - SPR_WALL_0000 + 1)
# define SPR_FILLER			18	// SPR_WALL_0000

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

void			sprite_overlay_gradient(t_sprite *spr, mlx_texture_t *gradient);
void			image_overlay_gradient(mlx_image_t *img, mlx_texture_t *gradient,
					uint32_t i);
void			bar_overlay_gradient(mlx_image_t *bar, mlx_texture_t *gradient,
					uint32_t i);
uint8_t			*gradient_read(mlx_texture_t *gradient, uint32_t i);

#endif
