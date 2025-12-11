/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:26:20 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/09 19:44:04 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes_src;
	unsigned char	*bytes_dest;

	if (!src && !dest)
		return (dest);
	bytes_src = (unsigned char *)src;
	bytes_dest = (unsigned char *)dest;
	while (n--)
		bytes_dest[n] = bytes_src[n];
	return (dest);
}
