/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:22:30 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/22 14:20:06 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	signe(const char *nptr)
{
	int	s;

	s = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			s = -1;
		else
			s = 1;
		nptr++;
	}
	return (s);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	s;

	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	s = signe(nptr);
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = 10 * n + *nptr - '0';
		nptr++;
	}
	return (s * n);
}
