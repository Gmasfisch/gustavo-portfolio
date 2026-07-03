/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:53:57 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/19 11:47:44 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;

	ptr_src = (const char *) src;
	ptr_dest = (char *) dest;
	if (dest == src)
		return (dest);
	if (dest < src)
		while (n--)
			*(ptr_dest++) = *(ptr_src++);
	else if (dest > src)
	{
		ptr_dest += n - 1;
		ptr_src += n - 1;
		while (n--)
			*(ptr_dest--) = *(ptr_src--);
	}
	return (dest);
}

/*int	main(void)
{
	char	*src = "Hello";
	char	dest[8] = "Goodbye";
	char *ptr = dest;
	int n = 5;

	ft_memmove(dest, src, n);
	while (n > 0)
	{
		printf("%c", *(ptr++));
		n--;
	}
}*/
