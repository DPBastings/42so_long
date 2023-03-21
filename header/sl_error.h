/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:20:47 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:50:09 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_ERROR_H
# define SL_ERROR_H

typedef enum e_sl_errno {
	SL_SUCCESS = 0,
	SL_GENERIC,
	SL_MEMFAIL,
	SL_INVARGS,
	SL_INVEXT,
	SL_INVPATH,
	SL_INVMAP_DIMS,
	SL_INVMAP_UNKNOWNOBJ,
	SL_INVMAP_BOUNDS,
	SL_INVMAP_NOSTART,
	SL_INVMAP_NOEXIT,
	SL_INVMAP_EXCSTART,
	SL_INVMAP_EXCEXIT,
	SL_INVMAP_NOCOLL,
	SL_INVMAP_NOPATH,
	N_SL_ERR,
}	t_sl_errno;

void		sl_strerror(t_sl_errno errno);
void		sl_error(t_sl_errno errno);

#endif
