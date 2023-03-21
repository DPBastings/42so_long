/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_message.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 17:23:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 17:41:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_MESSAGE_H
# define SL_MESSAGE_H

# include "MLX42/MLX42.h"
# include "mlx42_utils.h"
# include <stdint.h>

typedef struct s_message {
	mlx_image_t	*bg;
	mlx_image_t	*text;
}	t_message;

t_message	*message_init(mlx_t *mlx, mlx_texture_t *txr,
				uint32_t xy[2], uint32_t wh[2]);
void		message_write(t_message *msg, char const *str, t_style *style);
t_message	*message_destroy(t_message **msg, mlx_t *mlx);

#endif
