/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:16:33 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/10 13:20:34 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/

#include "libft.h"

static int	digit_counter(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		s;
	char	*num;

	s = 1;
	if (n < 0)
	{
		s = 2;
		n = -n;
	}
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num = (char *)malloc(sizeof(char) * (digit_counter(n) + s));
	if (!num)
		return (NULL);
	if (s == 2)
		num[0] = '-';
	num[digit_counter(n) + s - 1] = '\0';
	while (digit_counter(n) > 0)
	{
		num[digit_counter(n) + s - 2] = n % 10 + '0';
		n = n / 10;
	}
	return (num);
}
