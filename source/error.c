/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 16:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 15:23:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_error.h"

#include "libftprintf.h"
#include <stdlib.h>
#include <unistd.h>

static const char	*g_sl_errors[] = {
	"Everything went better than expected.",
	"Something went wrong.",
	"Couldn't allocate memory.",
	"Usage: so_long <map>.",
	"Invalid map file extension (it should be `.ber`).",
	"No file could be found at that location.",
	"That file doesn't constitute a valid map: invalid dimensions.",
	"That file doesn't constitute a valid map: contains invalid characters.",
	"That file doesn't constitute a valid map: it isn't enclosed in walls.",
	"That file doesn't constitute a valid map: there's no start.",
	"That file doesn't constitute a valid map: there's no exit.",
	"That file doesn't constitute a valid map: there's more than one start.",
	"That file doesn't constitute a valid map: there's more than one exit.",
	"That file doesn't constitute a valid map: there are no collectibles.",
	"That file doesn't constitute a valid map: the exit is unreachable.",
};

void	sl_error(t_sl_errno errno)
{
	sl_strerror(errno);
	exit(EXIT_FAILURE);
}

void	sl_strerror(t_sl_errno errno)
{	
	ft_dprintf(STDERR_FILENO, "Error\n[%02d] %s\n", errno, g_sl_errors[errno]);
}
