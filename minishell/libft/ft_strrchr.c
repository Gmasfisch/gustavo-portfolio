/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmasfisch <gmasfisch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:12:38 by mlemoula          #+#    #+#             */
/*   Updated: 2025/09/10 11:02:16 by gmasfisch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	ssize_t	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (c == '\0' || s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
