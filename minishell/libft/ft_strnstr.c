/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:20:14 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/09 19:43:37 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	while (len-- > 0 && *big)
	{
		if (*big == *little)
		{
			i = 0;
			while (*(little + i) && \
			*(big + i) == *(little + i)
				&& len - i + 1 > 0)
				i++;
			if (i == ft_strlen(little))
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
