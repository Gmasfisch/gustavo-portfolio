/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:07:58 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/26 12:17:55 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	d;

	ptr = (char *) s;
	d = (unsigned) c;
	while (*ptr)
		ptr++;
	while (ptr - (char *) s != 0 && *ptr != d)
		ptr--;
	if (*ptr == d)
		return (ptr);
	else
		return (0);
}

/*int main(void)
{
	char a[] = "";
	int	c = '\0';

	printf("%s", ft_strrchr(a, c));
}*/