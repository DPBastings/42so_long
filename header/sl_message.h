/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_message.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 17:23:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 11:44:51 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_MESSAGE_H
# define SL_MESSAGE_H

# include "MLX42/MLX42.h"
# include "mlx42_utils.h"
# include <stdint.h>

# define CAPTION_SIZE	2
# define CAPTION_COLOUR	0xAEA7A0FF
# define BODY_OFFSET	40
# define BODY_SIZE		1
# define BODY_COLOUR	0xA6907BFF

typedef struct s_message {
	mlx_image_t		*bg;
	mlx_image_t		*text;
}	t_message;

t_message	*message_init(mlx_t *mlx, mlx_texture_t *txr,
				uint32_t const xy[2], uint32_t const wh[2]);
void		message_print_body(t_message *msg, char const *caption,
				mlx_texture_t *font);
void		message_print_caption(t_message *msg, char const *caption,
				mlx_texture_t *font);
void		message_destroy(t_message **msg, mlx_t *mlx);

#endif
