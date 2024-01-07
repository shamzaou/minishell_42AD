/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 03:03:50 by alabdull          #+#    #+#             */
/*   Updated: 2024/01/08 03:05:27 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd1(char *s1, int n, char *s3, int fd)
{
	if (s1 != 0 && s3 != 0)
	{
		write(fd, s1, ft_strlen(s1));
		ft_putnbr_fd(n, fd);
		write(fd, s3, ft_strlen(s3));
	}
}
