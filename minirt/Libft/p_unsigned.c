/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_unsigned.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:44:07 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 10:44:29 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	putnbr(unsigned int nbr, int *count)
{
	if (nbr / 10 > 0)
		putnbr(nbr / 10, count);
	ft_putchar((nbr % 10) + '0');
	(*count)++;
}

void	p_unsigned(unsigned int nbr, int *count)
{
	putnbr(nbr, count);
}
