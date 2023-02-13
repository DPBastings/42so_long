/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 16:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 15:08:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libftprintf.h"
#include <stdlib.h>

static const char	*g_sl_errors[] = {
	"Everything went better than expected.",
	"Couldn't allocate memory.",
	"Bad asset detected.",
	"Usage: so_long <map>.",
	"Invalid map file extension (it should be `.ber`).",
	"No file could be found at that location.",
	"That file doesn't constitute a valid map.",
};

void	sl_error(int errno)
{
	sl_strerror(errno);
	exit(EXIT_FAILURE);
}

void	sl_strerror(int errno)
{
	ft_dprintf(2, "Error\n%s\n", g_sl_errors[errno]);
}
