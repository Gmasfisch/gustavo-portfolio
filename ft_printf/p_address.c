/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_address.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:35:26 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/29 13:57:24 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(unsigned long long n, int *count)
{
	if (n >= 16)
		ft_puthex(n / 16, count);
	ft_putchar("0123456789abcdef"[n % 16]);
	(*count)++;
}

void	p_address(void *pointer, int *count)
{
	if (!pointer)
	{
		write(1, "(nil)", 5);
		*count += 5;
		return ;
	}
	write(1, "0x", 2);
	(*count) += 2;
	ft_puthex((unsigned long long) pointer, count);
}
