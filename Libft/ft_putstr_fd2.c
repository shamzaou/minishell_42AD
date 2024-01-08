/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou@student.42abudhabi.ae <shamzaou>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 02:49:25 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/09 02:20:20 by shamzaou@student ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd2(char *s1, char s2, char *s3, int fd)
{
	if (s1 != 0 && s2 != 0)
	{
		write(fd, s1, ft_strlen(s1));
		write(fd, &s2, 1);
		write(fd, s3, ft_strlen(s3));
	}
}
