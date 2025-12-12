/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:57:00 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 18:00:21 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned char	d;

	d = (unsigned char ) c;
	ptr = (unsigned char *)s;
	while (*ptr && *ptr != d)
		ptr++;
	if (*ptr == d)
		return ((char *) ptr);
	return (0);
}

// int main(void)
// {
// char a[] = "hello";
// int	c = 'l';
//
// printf("%s", ft_strchr(0x59f0b0a07020: "teste", 357: 'e'));
// }
