/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:20:57 by alabdull          #+#    #+#             */
/*   Updated: 2022/12/02 19:56:19 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, char c)
{
	int		count;
	char	*hex;

	count = 1;
	if (c == 'X')
		hex = "0123456789ABCDEF";
	if (c == 'x')
		hex = "0123456789abcdef";
	if (n > 15)
		count += ft_puthex(n / 16, c);
	ft_putchar(hex[n % 16]);
	return (count);
}

int	print_hex(va_list args, char c)
{
	int	count;
	int	n;

	n = va_arg(args, unsigned int);
	count = ft_puthex(n, c);
	return (count);
}
