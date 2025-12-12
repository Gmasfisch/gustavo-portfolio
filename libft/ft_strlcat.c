/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:13:31 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/19 11:10:13 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		counter_d;
	size_t		counter_s;

	counter_d = 0;
	counter_s = 0;
	while ((dst[counter_d] != '\0') && counter_d < size)
		counter_d++;
	while (src[counter_s] != '\0')
		counter_s++;
	if (size == 0)
		return (counter_s);
	if (size <= counter_d)
		return (size + counter_s);
	i = 0;
	while (src[i] != '\0' && (i + counter_d) < (size - 1))
	{
		dst [counter_d + i] = src[i];
		i++;
	}
	dst[counter_d + i] = '\0';
	return (counter_d + counter_s);
}

/*int	main(void)
{
	char	a[] = "Hello";
	char	b[] = "Gu";

	//ft_strlcat(a, b, 6);
	printf("%s %ld", a, ft_strlcat(a, b, 7));
}*/
