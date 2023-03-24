/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_general.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 18:12:27 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 10:53:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_GENERAL_H
# define SL_GENERAL_H

# define GRID_W				48
# define GRID_H				48
//SCREEN_W = (GRID_W * 26); SCREEN_H = (GRID_H * 15)
# define SCREEN_W			1248
# define SCREEN_H			720

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
	Z_FG0,
	Z_FG1,
}	t_z;

#endif
