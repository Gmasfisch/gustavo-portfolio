/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:10:48 by mlemoula          #+#    #+#             */
/*   Updated: 2024/12/11 18:40:13 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	%c Prints a single character.
	%s Prints a string (as defined by the common C convention).
	%p The void * pointer argument has to be printed in hexadecimal format.
	%d Prints a decimal (base 10) number.
	%i Prints an integer in base 10.
	%u Prints an unsigned decimal (base 10) number.
	%x Prints a number in hexadecimal (base 16) lowercase format.
	%X Prints a number in hexadecimal (base 16) uppercase format.
	%% Prints a percent sign.

cspdiuxX%
*/

static int	check_parameter(char param)
{
	if (param == 'c' || param == 's' || param == 'p' || param == 'd'
		|| param == 'i' || param == 'u' || param == 'x'
		|| param == 'X' || param == '%')
		return (1);
	return (0);
}

static int	check_format(const char *format, va_list args)
{
	int	print_count;

	print_count = 0;
	if (*(format + 1) == 'c')
		ft_print_pc((char *)(format + 1),
			va_arg(args, int), &print_count);
	if (*(format + 1) == '%')
		ft_print_pc((char *)(format + 1), '%', &print_count);
	else if (*(format + 1) == 's')
		ft_print_s((char *)va_arg(args, char *), &print_count);
	else if (*(format + 1) == 'p')
		ft_print_p(va_arg(args, void *), &print_count);
	else if (*(format + 1) == 'd' || *(format + 1) == 'i')
		ft_print_id(va_arg(args, int), &print_count);
	else if (*(format + 1) == 'u')
		ft_print_u(va_arg(args, int), &print_count);
	else if (*(format + 1) == 'x' || *(format + 1) == 'X')
		ft_print_x_upx(va_arg(args, int), &print_count, *(format + 1));
	if (!(check_parameter(*(format + 1))))
	{
		write (1, format, 2);
		print_count += 2;
	}
	return (print_count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		tmp;
	int		print_count;

	if (!format)
		return (-1);
	print_count = 0;
	va_start(args, format);
	while (*format)
	{
		while (*format && *format != '%')
		{
			write (1, format, 1);
			format++;
			print_count++;
		}
		if (*format == '%' && *(format + 1))
		{
			tmp = check_format(format, args);
			print_count += tmp;
			format += 2;
		}
	}
	va_end(args);
	return (print_count);
}
