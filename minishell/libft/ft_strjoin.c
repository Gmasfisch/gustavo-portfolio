/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:20:54 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/18 15:40:36 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*concat;

	if (!s1 && !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	concat = malloc((i + 1) * sizeof(char const));
	if (!concat)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		concat[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		concat[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	concat[ft_strlen(s1) + i] = '\0';
	return (concat);
}
