/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_csdp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:35:08 by mlemoula          #+#    #+#             */
/*   Updated: 2024/12/11 18:43:48 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_pc(char *s, char arg, int *print_count)
{
	if (*s == '%')
		arg = '%';
	write (1, &arg, 1);
	*print_count += 1;
}

void	ft_print_s(char *arg, int *print_count)
{
	int	i;

	i = 0;
	if (!arg)
	{
		write (1, "(null)", 6);
		*print_count += 6;
		return ;
	}
	while (*(arg + i))
	{
		write (1, arg + i, 1);
		i++;
	}
	*print_count += i;
}

void	ft_print_id(int arg, int *print_count)
{
	char	*tmp;

	ft_putnbr_fd(arg, 1);
	tmp = ft_itoa(arg);
	if (!tmp)
		return ;
	*print_count += ft_strlen(tmp);
	free (tmp);
}
