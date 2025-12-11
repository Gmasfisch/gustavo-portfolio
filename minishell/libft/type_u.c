/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:58:46 by mlemoula          #+#    #+#             */
/*   Updated: 2024/12/11 18:43:58 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int n)
{
	if (n > 9)
		ft_putnbr_unsigned(n / 10);
	ft_putnbr_fd(n % 10, 1);
}

void	ft_print_u(unsigned int arg, int *print_count)
{
	int	i;

	i = 0;
	if ((int)arg == 0)
	{
		write (1, "0", 1);
		i = 1;
	}
	else
	{
		ft_putnbr_unsigned(arg);
		while (arg > 0)
		{
			arg = arg / 10;
			i++;
		}
	}
	*print_count += i;
}
