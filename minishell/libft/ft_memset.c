/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:09:25 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/08 18:15:09 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*bytes_array;

	bytes_array = s;
	i = 0;
	while (i < n)
	{
		bytes_array[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
