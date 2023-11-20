/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:45:14 by alabdull          #+#    #+#             */
/*   Updated: 2022/10/16 15:11:51 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*map;

	if (!s || !f)
		return (NULL);
	map = ft_strdup(s);
	if (!map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		map[i] = f(i, map[i]);
		i++;
	}
	return (map);
}
