/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:20:00 by alabdull          #+#    #+#             */
/*   Updated: 2022/11/15 21:00:18 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(va_list args)
{
	int	count;
	int	n;

	n = va_arg(args, int);
	count = ft_putnbr(n);
	return (count);
}
