/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 17:21:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 11:56:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_message.h"
#include "sl_error.h"
#include "sl_general.h"
#include "sl_image.h"

#include "MLX42/MLX42.h"
#include <stdint.h>
#include <stdlib.h>

#define	MARGIN	12

static void	msg_render(t_message *msg, mlx_t *mlx, uint32_t const xy[2]);

t_message	*message_init(mlx_t *mlx, mlx_texture_t *txr,
				uint32_t const xy[2], uint32_t const wh[2])
{
	t_message		*msg;
	uint32_t const	gridsize[2] = {GRID_W, GRID_H};

	if (wh[2] <= BODY_OFFSET || wh[0] <= 2 * MARGIN || wh[1] <= 2 * MARGIN)
		sl_error(SL_GENERIC);
	msg = malloc(sizeof(t_message));
	if (msg == NULL)
		sl_error(SL_MEMFAIL);
	msg->bg = image_init(mlx, wh[0], wh[1]);
	msg->text = image_init(mlx, wh[0] - 2 * MARGIN, wh[1] - 2 * MARGIN);
	image_tile(msg->bg, txr, gridsize);
	msg_render(msg, mlx, xy);
	return (msg);
}

void	message_destroy(t_message **msg, mlx_t *mlx)
{
	mlx_delete_image(mlx, (*msg)->bg);
	mlx_delete_image(mlx, (*msg)->text);
	free(*msg);
	*msg = NULL;
}

static void	msg_render(t_message *msg, mlx_t *mlx, uint32_t const xy[2])
{
	int32_t	id;

	id = image_render(mlx, msg->bg, xy[0], xy[1]);
	mlx_set_instance_depth(&msg->bg->instances[id], Z_FG0);
	id = image_render(mlx, msg->text, xy[0] + MARGIN, xy[1] + MARGIN);
	mlx_set_instance_depth(&msg->text->instances[id], Z_FG1);
}
