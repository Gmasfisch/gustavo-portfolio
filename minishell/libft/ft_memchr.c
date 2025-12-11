/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:33:37 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/14 13:07:56 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*bytes;

	bytes = (unsigned char *)s;
	while (n > 0)
	{
		if (*bytes == (unsigned char)c)
			return (bytes);
		bytes++;
		n--;
	}
	return (NULL);
}
