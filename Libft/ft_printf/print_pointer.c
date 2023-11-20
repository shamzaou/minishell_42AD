/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:24:37 by alabdull          #+#    #+#             */
/*   Updated: 2023/01/30 16:55:38 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(size_t n, char *s)
{
	int	c;

	c = 0;
	if (n >= 16)
		c += ft_putpointer(n / 16, s);
	ft_putchar(s[n % 16]);
	c++;
	return (c);
}

int	print_pointer(va_list args)
{
	int		count;
	size_t	n;

	n = va_arg(args, size_t);
	ft_putstr("0x");
	count = ft_putpointer(n, "0123456789abcdef");
	return (count + 2);
}
