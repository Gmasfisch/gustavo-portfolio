/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:14:55 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/09 19:44:09 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*bytes_src;
	unsigned char		*bytes_dest;
	size_t				i;

	bytes_src = src;
	bytes_dest = dest;
	i = 0;
	if (!src && !dest)
		return (dest);
	if (src >= dest)
	{
		while (i < n)
		{
			bytes_dest[i] = bytes_src[i];
			i++;
		}
	}
	else
		while (n-- > 0)
			bytes_dest[n] = bytes_src[n];
	return (dest);
}
