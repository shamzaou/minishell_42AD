/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:05:45 by alabdull          #+#    #+#             */
/*   Updated: 2023/01/30 20:34:53 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_convert(va_list args, const char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = print_char(args);
	else if (c == 's')
		count += print_str(args);
	else if (c == 'i' || c == 'd')
		count += print_int(args);
	else if (c == 'x' || c == 'X')
		count += print_hex(args, c);
	else if (c == 'p')
		count += print_pointer(args);
	else if (c == 'u')
		count += print_uint(args);
	else if (c == '%')
		count += ft_printchar(c);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			count += ft_convert(args, s[i + 1]);
			i++;
		}
		else
			count += ft_printchar(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}
// #include "stdio.h"
// int main()
// {
// 	printf("\n%d\n",ft_printf("%%%"));
// 	printf("\n%d\n",printf("%%%"));
// }