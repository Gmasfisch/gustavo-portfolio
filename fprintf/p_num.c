/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_num.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:39:13 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 11:05:27 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr(int num, int *count)
{
	unsigned int	nbr;

	if (num < 0)
	{
		ft_putchar('-');
		(*count)++;
		nbr = -num;
	}
	else
		nbr = num;
	if (nbr / 10 > 0)
		putnbr(nbr / 10, count);
	ft_putchar((nbr % 10) + '0');
	(*count)++;
}

void	p_num(int num, int *count)
{
	putnbr(num, count);
}
