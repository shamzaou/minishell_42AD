/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:21:33 by alabdull          #+#    #+#             */
/*   Updated: 2022/12/30 21:05:03 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static int	ft_wordlen(char const *s, char c, int j)
{
	size_t	i;

	i = 0;
	while (s[j + i] != c && s[j + i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, ft_wordlen(s, c, i));
			i += ft_wordlen(s, c, i);
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}
