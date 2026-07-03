/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:15:05 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 18:04:01 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (*s1 != *s2)
			return ((unsigned char )*s1 - (unsigned char )*s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
}

/*int	main(void)
{
	char	a[] = "abcdefgh";
	char	b[] = "abcdwxyz";

	int c = ft_strncmp(a, b, 4);
	printf("%i", c);
}*/
