/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:40:02 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/09 19:44:19 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.*/

#include "libft.h"

static int	ft_check_char(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	char	*trimstr;
	int		trimlen;
	int		i;

	if (!s1 || !set)
		return (NULL);
	while (ft_check_char(*s1, set) > 0 && *s1)
		s1++;
	trimlen = ft_strlen(s1);
	while (trimlen > 0 && ft_check_char(s1[trimlen - 1], set) > 0)
		trimlen --;
	trimstr = malloc((trimlen + 1) * (sizeof(char const)));
	if (!trimstr)
		return (NULL);
	i = 0;
	while (i < trimlen)
	{
		trimstr[i] = *s1;
		i++;
		s1++;
	}
	trimstr[i] = '\0';
	return (trimstr);
}
