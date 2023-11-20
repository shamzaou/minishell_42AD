/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:36:46 by alabdull          #+#    #+#             */
/*   Updated: 2023/01/11 21:30:04 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (len > i)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
}

int	ft_numlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		i;
	int			is_neg;
	char		*value;

	is_neg = (n < 0);
	value = malloc(ft_numlen(n) + 1);
	if (!value)
		return (NULL);
	value[ft_numlen(n)] = '\0';
	if (n == 0)
		value[0] = '0';
	i = 0;
	while (n != 0)
	{
		value[i++] = '0' + ft_nbr(n % 10);
		n = (n / 10);
	}
	if (is_neg)
		value[i] = '-';
	ft_strrev(value);
	return (value);
}
