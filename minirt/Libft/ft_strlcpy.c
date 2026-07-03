/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:59:32 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/19 11:10:15 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;
	size_t	sizecpy;
	char	*ptr_src;
	char	*ptr_dst;

	ptr_src = (char *) src;
	ptr_dst = (char *) dst;
	sizecpy = size;
	counter = 0;
	while (*(ptr_src++))
		counter++;
	if (size == 0)
		return (counter);
	ptr_src = (char *) src;
	while (sizecpy-- > 1 && *ptr_src)
		*(ptr_dst++) = *(ptr_src++);
	*ptr_dst = '\0';
	return (counter);
}

/*int	main(void)
{
	char *src = "Hello";
	char dest[8] = "Goodbye";
	int length = ft_strlcpy(dest, src, 6);

	printf("%i, %s", length, dest);
}*/