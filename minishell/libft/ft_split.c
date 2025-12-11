/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:23:13 by mlemoula          #+#    #+#             */
/*   Updated: 2025/06/10 19:24:30 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/

#include "libft.h"

static int	split_counter(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char	*ft_custom_strdup(const char *s, char c)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**free_all_str(char **str_array, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(str_array[i]);
		i++;
	}
	free (str_array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**str_array;

	str_array = (char **)malloc((split_counter(s, c) + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			str_array[j] = ft_custom_strdup(s, c);
			if (!str_array[j])
				return (free_all_str(str_array, j));
			s++;
			j++;
		}
		while (*s != c && *s)
			s++;
	}
	str_array[j] = NULL;
	return (str_array);
}
