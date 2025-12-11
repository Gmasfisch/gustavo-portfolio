/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:25:19 by mlemoula          #+#    #+#             */
/*   Updated: 2024/12/12 12:16:21 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The void * pointer argument is printed in hexadecimal (as if  by %#x or %#lx).
*/

#include "ft_printf.h"

static int	print_hex(unsigned long long nbr)
{
	char	*base16;
	int		counter;

	counter = 0;
	base16 = "0123456789abcdef";
	if (nbr > 15)
		counter += print_hex(nbr / 16);
	write(1, base16 + (nbr % 16), 1);
	return (counter + 1);
}

void	ft_print_p(void *ptr, int *print_count)
{
	unsigned long long	mem_address;

	if (ptr)
	{
		mem_address = (unsigned long long)ptr;
		write(1, "0x", 2);
		*print_count += 2 + print_hex(mem_address);
	}
	else
	{
		write(1, "(nil)", 5);
		*print_count += 5;
	}
}
