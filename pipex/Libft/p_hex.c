/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:34:31 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 11:06:16 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_hex(unsigned int nbr, int *count, const char *format)
{
	char	*hex_digits;

	if (*format == 'x')
		hex_digits = "0123456789abcdef";
	else
		hex_digits = "0123456789ABCDEF";
	if (nbr / 16)
		p_hex(nbr / 16, count, format);
	ft_putchar(hex_digits[nbr % 16]);
	(*count)++;
}
