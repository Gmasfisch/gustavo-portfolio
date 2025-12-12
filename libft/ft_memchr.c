/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:35:35 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/19 15:29:35 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_char;
	size_t			i;

	ptr_char = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (*ptr_char == (unsigned char) c)
			return ((void *) ptr_char);
		ptr_char++;
		i++;
	}
	return (0);
}
