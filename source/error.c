/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 16:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/28 10:50:24 by dbasting      ########   odam.nl         */
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
	"File doesn't constitute a valid map: invalid dimensions.",
	"File doesn't constitute a valid map: contains invalid characters.",
	"File doesn't constitute a valid map: it isn't enclosed in walls.",
	"File doesn't constitute a valid map: there's no start.",
	"File doesn't constitute a valid map: there's no exit.",
	"File doesn't constitute a valid map: there's more than one start.",
	"File doesn't constitute a valid map: there's more than one exit.",
	"File doesn't constitute a valid map: there are no collectibles.",
	"File doesn't constitute a valid map: the exit is unreachable.",
	"File doesn't constitute a valid map: some collectibles can't be reached.",
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
