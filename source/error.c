/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 16:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 17:50:51 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libftprintf.h"
#include <stdlib.h>

static const char	*sl_errors[] = {
	"Everything went better than expected.",
	"Couldn't allocate memory.",
	"Usage: so_long [map].",
	"Invalid map file extension.",
	"Couldn't read map from file.",
	"That map doesn't constitute a valid level.",
};

void	sl_error(int errno)
{
	sl_strerror(errno);
	exit(EXIT_FAILURE);
}

void	sl_strerror(int errno)
{
	ft_dprintf(2, "Error\n%s\n", sl_errors[errno]);
}
