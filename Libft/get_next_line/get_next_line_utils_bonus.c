/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:29:03 by alabdull          #+#    #+#             */
/*   Updated: 2023/02/08 21:43:52 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == 0)
		return (s);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (s);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	result = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[gnl_strlen(s1) + gnl_strlen(s2)] = '\0';
	free(s1);
	return (result);
}

char	*ft_get_line(char *s)
{
	int		i;
	char	*result;

	i = 0;
	if (!*s)
		return (NULL);
	result = malloc(gnl_strlen(s) + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		result[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_save_str(char *s)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	result = malloc(gnl_strlen(s) - i + 1);
	if (!result)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
	{
		result[j++] = s[i++];
	}
	result[j] = '\0';
	free(s);
	return (result);
}
