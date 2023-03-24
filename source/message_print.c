/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message_print.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 10:54:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 11:50:24 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_message.h"
#include "mlx42_utils.h"

void	message_print_caption(t_message *msg, char const *caption,
			mlx_texture_t *font)
{
	uint32_t	p[2];
	t_style		style;

	p[0] = 0;
	p[1] = 0;
	style.font = font;
	style.size = CAPTION_SIZE;
	style.colour = CAPTION_COLOUR;
	string_to_image(caption, msg->text, p, &style);
}

void	message_print_body(t_message *msg, char const *text,
			mlx_texture_t *font)
{
	uint32_t	p[2];
	t_style		style;
	
	p[0] = 0;
	p[1] = BODY_OFFSET;
	style.font = font;
	style.size = BODY_SIZE;
	style.colour = BODY_COLOUR;
	string_to_image(text, msg->text, p, &style);
}
