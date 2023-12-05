/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:05:35 by shamzaou          #+#    #+#             */
/*   Updated: 2023/12/05 12:18:33 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char *ft_strtolower(char *str)
{
	int i;
	char *low;
	
	i = 0;
	if (!str)
		return (NULL);
	low = str;
	while (str[i])
	{
		low[i] = ft_tolower(str[i]);
		i++;
	}
	return (low);
}