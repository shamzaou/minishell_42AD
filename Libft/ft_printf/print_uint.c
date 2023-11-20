/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:21:06 by alabdull          #+#    #+#             */
/*   Updated: 2022/12/02 19:56:31 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(size_t n)
{
	int	count;

	count = 1;
	if (n > 9)
		count += ft_putunbr(n / 10);
	ft_putchar(n % 10 + '0');
	return (count);
}

int	print_uint(va_list args)
{
	unsigned int	n;
	int				count;

	n = va_arg(args, unsigned int);
	count = ft_putunbr(n);
	return (count);
}
