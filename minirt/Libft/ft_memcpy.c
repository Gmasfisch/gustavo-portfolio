/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:20:32 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 15:06:35 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dest;

	ptr_src = (unsigned char *) src;
	ptr_dest = (unsigned char *) dest;
	if (!src && !dest)
		return (NULL);
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}

/*int	main(void)
{
	char	*src = "Hello";
	char	dest[8] = "Goodbye";
	char *ptr = dest;
	int n = 5;

	ft_memcpy(dest, src, n);
	while (n > 0)
	{
		printf("%c", *(ptr++));
		n--;
	}
}*/
