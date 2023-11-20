/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <alabdull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:20:51 by alabdull          #+#    #+#             */
/*   Updated: 2022/12/02 00:15:39 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		print_char(va_list args);
int		print_hex(va_list args, char c);
int		print_int(va_list args);
int		print_pointer(va_list args);
int		print_str(va_list args);
int		print_uint(va_list args);
int		ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);

#endif