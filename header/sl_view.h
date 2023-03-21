/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_view.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:23:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:12:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_VIEW_H

# define SL_VIEW_H

# include "sl_general.h"
# include "sl_object.h"

# include "point.h"
# include <stdint.h>

//VIEW_MAXW = SCREEN_W; VIEW_MAXH = (SCREEN_H - HUD_H)
# define VIEW_MAXW	1248
# define VIEW_MAXH	576

/* View object.
 * @param origin		The coordinate from which the current camera view originates.
 * @param origin_max	The greatest valid value for `origin`.
 * @param port_min		The top left corner of the viewport.
 * @param port_max		The bottom right corner of the viewport.
 */
typedef struct s_view {
	t_point		origin;
	t_point		origin_max;
	t_point		port_min;
	t_point		port_max;
}	t_view;

void		view_init(t_view *view, t_upoint map_dims);
int32_t		view_xview(int32_t x, t_view view);
int32_t		view_yview(int32_t y, t_view view);
uint32_t	view_xgrid(int32_t x, t_view view);
uint32_t	view_ygrid(int32_t y, t_view view);
void		view_update(t_view *view, t_point diff, t_map *map);
void		view_centre(t_view *view, t_point anchor, t_map *map);
void		view_shift(t_view *view, t_point anchor, t_map *map);

#endif
