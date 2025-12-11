/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:51:02 by gfischba          #+#    #+#             */
/*   Updated: 2025/01/27 11:52:57 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		in_word;
	int		count;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	*free_array(char **array, int i)
{
	while (i >= 0)
	{
		free (array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

static	char	**fill_array(char **array, const char *s, char c, int words)
{
	int			i;
	int			len;
	char		*word;

	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		word = malloc(len + 1);
		if (!word)
			return (free_array(array, i - 1));
		array[i] = word;
		while (*s != c && *s)
			*word++ = *s++;
		*word = '\0';
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	if (!fill_array(array, s, c, words))
		return (NULL);
	return (array);
}

//int main(void)
//{
//	int i = 0;
//	const char *string = "Hello, World, How, Are, You";
//	char delimiter = ',';
//	char **array = ft_split(string, delimiter);
//	while (i < 20)
//	{
//		printf("%s", array[i]);
//		i++;
//	}
//}