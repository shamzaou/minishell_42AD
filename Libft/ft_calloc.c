/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 06:42:40 by alabdull          #+#    #+#             */
/*   Updated: 2022/11/02 19:18:06 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*h;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	i = count * size;
	h = malloc(i);
	if (!h)
		return (NULL);
	ft_memset(h, 0, i);
	return (h);
}
