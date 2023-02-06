/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 14:14:08 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 14:45:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_talloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (*ptr == NULL)
		return (0);
	return (1);
}

int	ft_tcalloc(void **ptr, size_t count, size_t size)
{
	*ptr = malloc(size);
	if (*ptr == NULL)
		return (0);
	ft_memset(*ptr, '\0', count * size);
	return (1);
}
