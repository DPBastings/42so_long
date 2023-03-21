/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_sprite_setup.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 12:16:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 12:17:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_SPRITE_SETUP_H
# define SL_SPRITE_SETUP_H

typedef void			(*t_spr_setter)(t_object *obj, t_game *game);
void		sprite_set_default(t_object *obj, t_game *game);
void		sprite_set_coll(t_object *obj, t_game *game);
void		sprite_set_enemy(t_object *obj, t_game *game);
void		sprite_set_wall(t_object *obj, t_game *game);

#endif
