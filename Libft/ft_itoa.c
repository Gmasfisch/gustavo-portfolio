/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:49:17 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/22 23:25:23 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_characters(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*store_numbers(int n, char *string, int chars)
{
	unsigned int	nbr;
	int				charcpy;

	charcpy = chars;
	if (n == 0)
	{
		string[0] = '0';
		string[chars] = '\0';
		return (string);
	}
	if (n < 0)
	{
		string[0] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	while (nbr != 0)
	{
		string[chars - 1] = (nbr % 10) + '0';
		nbr /= 10;
		chars--;
	}
	string[charcpy] = '\0';
	return (string);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	chars;

	chars = count_characters(n);
	string = malloc(chars + 1);
	if (!string)
		return (NULL);
	string = store_numbers(n, string, chars);
	return (string);
}

/*int	main (void)
{
	char *c = ft_itoa(INT_MAX);
	printf("%s", c);
}*/