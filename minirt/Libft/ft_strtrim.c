/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:02:12 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/27 16:50:32 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(const char	*s1, const char	*set);
static int	find_end(const char	*s1, const char	*set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_i;
	int		end_i;
	int		j;
	char	*new_string;

	j = 0;
	start_i = find_start(s1, set);
	end_i = find_end(s1, set);
	if (end_i < start_i)
		return (ft_strdup(""));
	new_string = malloc((end_i - start_i + 2) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (start_i <= end_i)
		new_string[j++] = s1[start_i++];
	new_string[j] = '\0';
	return (new_string);
}

static int	find_start(const char	*s1, const char	*set)
{
	int	start_i;
	int	j;

	start_i = 0;
	while (s1[start_i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[start_i] == set[j])
				break ;
			j++;
		}
		if (set[j] == '\0')
			break ;
		start_i++;
	}
	return (start_i);
}

static int	find_end(const char	*s1, const char	*set)
{
	int	end_i;
	int	j;

	end_i = ft_strlen(s1) - 1;
	while (end_i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[end_i] == set[j])
				break ;
			j++;
		}
		if (set[j] == '\0')
			break ;
		end_i--;
	}
	return (end_i);
}
