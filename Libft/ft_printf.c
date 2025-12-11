/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:18:14 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 13:59:03 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c);
void	checker(va_list args, const char *format, int *count);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			checker(args, format, &count);
		}
		else
		{
			ft_putchar(*format);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

void	checker(va_list args, const char *format, int *count)
{
	if (*format == 's')
		p_string(va_arg(args, char *), count);
	else if (*format == 'c')
	{
		ft_putchar((char) va_arg(args, int));
		(*count)++;
	}
	else if (*format == 'i' || *format == 'd')
		p_num(va_arg(args, int), count);
	else if (*format == 'x' || *format == 'X')
		p_hex(va_arg(args, unsigned int), count, format);
	else if (*format == 'u')
		p_unsigned(va_arg(args, unsigned int), count);
	else if (*format == 'p')
		p_address(va_arg(args, void *), count);
	else if (*format == '%')
	{
		ft_putchar('%');
		(*count)++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*int main(void)
{
    ft_printf("Int: %d\n", 42); 
	ft_printf("Int: %d\n", -42);
	printf("Int: %d\n", -42);

	ft_printf("Unsigned: %u\n", 42);
	ft_printf("Unsigned: %u\n", -42);
	printf("Unsigned: %u\n", -42); 

	ft_printf("Hex: %x\n", 42);  
	ft_printf("Hex: %x\n", 255);
	printf("Unsigned: %u\n", -42);

	ft_printf("Hex (upper): %X\n", 42);   
	ft_printf("Hex (upper): %X\n", 255);
	printf("Hex (upper): %X\n", 255);
	//int x = 42;
	ft_printf("Pointer: %p\n", -1);
	//printf("%p\n", 16);

	ft_printf("String: %s\n", "Hello, World!");
	ft_printf("String: %s\n", NULL);
	//printf("String: %s\n", NULL);

	ft_printf("Char: %c\n", 'A');   // Should print: Char: A
	ft_printf("Char: %c\n", '\n');

	ft_printf("Int: %d\n", 0);   // Should print: Int: 0
	ft_printf("Unsigned: %u\n", 0);  // Should print: Unsigned: 0
	ft_printf("Hex: %x\n", 0); 

	ft_printf("Int: %d\n", -2147483648);  // Should print: Int: -2147483648
	ft_printf("Int: %d\n", 2147483647);

	ft_printf("Unsigned: %u\n", 4294967295);
	ft_printf("String: %%\n", "");

	ft_printf("String: %s\n", NULL);  // Should print: String: (null)
	ft_printf("Pointer: %p\n", NULL); // Should print: Pointer: (nil)	
    return 0;
}*/
