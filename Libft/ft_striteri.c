/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:04:01 by alabdull          #+#    #+#             */
/*   Updated: 2022/11/25 10:09:26 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return ;
	i = ft_strlen(s);
	while (j < i)
	{
		(*f)(j, s);
		s++;
		j++;
	}
}
