/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:15:59 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/12 15:46:13 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;
	size_t	dst_length;

	i = 0;
	src_length = ft_strlen (src);
	dst_length = ft_strlen (dst);
	if (size <= dst_length)
		return (src_length + size);
	while (i + dst_length < size - 1 && src[i])
	{
		dst[i + dst_length] = src[i];
		i++;
	}
	dst[i + dst_length] = '\0';
	return (dst_length + src_length);
}
