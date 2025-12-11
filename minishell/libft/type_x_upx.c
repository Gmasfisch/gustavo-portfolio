/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_x_upx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:25:19 by mlemoula          #+#    #+#             */
/*   Updated: 2024/12/11 18:44:02 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex(unsigned int nbr, char c)
{
	char	*base16;
	int		counter;

	counter = 0;
	if (c == 'x')
		base16 = "0123456789abcdef";
	else
		base16 = "0123456789ABCDEF";
	if (nbr > 15)
		counter += print_hex(nbr / 16, c);
	write(1, base16 + (nbr % 16), 1);
	return (counter + 1);
}

void	ft_print_x_upx(unsigned int arg, int *print_count, char c)
{
	int				i;
	unsigned int	tmp;

	i = 0;
	if ((int)arg == -2147483648)
	{
		write (1, "80000000", 8);
		i = 8;
	}
	else
	{
		if (arg == 0)
			i = 1;
		tmp = arg;
		while (tmp > 0)
		{
			tmp = tmp / 16;
			i++;
		}
		print_hex(arg, c);
	}
	*print_count += i;
}
