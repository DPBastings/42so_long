/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_destroy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 12:11:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/20 12:12:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	map_destroy(t_map **map)
{
	char	**tmp;

	tmp = (*map)->objs;
	while (tmp)
	{
		free(*tmp);
		tmp++;
	}
	free((*map)->objs);
	free(*map);
	*map = NULL;
}
