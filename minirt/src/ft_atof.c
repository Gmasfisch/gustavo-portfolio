/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:35:57 by gfischba          #+#    #+#             */
/*   Updated: 2026/02/07 13:35:58 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	parse_fraction(const char **str)
{
	float	frac;
	float	div;

	div = 10;
	frac = 0;
	while (ft_isdigit(**str))
	{
		frac += (**str - '0') / div;
		div *= 10;
		(*str)++;
	}
	return (frac);
}

float	ft_atof(const char *str)
{
	float	res;
	float	sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		res += parse_fraction(&str);
	}
	return (res * sign);
}
