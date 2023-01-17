/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:20:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/09 15:41:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	map_delete(void *content)
{
	free(content);
}

t_map	*map_read(char const *filename)
{
	t_map	*map;
	int		fd;
	char	*line;
	size_t	width;

	map = NULL;
	fd = open(filename, O_RDONLY);
	line = ft_getline(fd);
	width = ft_strlen(line);
	while (line)
	{
		if (ft_strlen(line) != width)
			return (ft_lstclear(&map, map_delete), NULL);
		ft_lstadd_back(&map, ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
}
