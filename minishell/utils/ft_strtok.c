/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:32:01 by gfischba          #+#    #+#             */
/*   Updated: 2025/10/02 19:01:48 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*input;
	char		*start;

	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	while (*input && ft_strchr(delim, *input))
		input++;
	if (*input == '\0')
		return (NULL);
	start = input;
	while (*input && !ft_strchr(delim, *input))
		input++;
	if (*input)
	{
		*input = '\0';
		input++;
	}
	else
		input = NULL;
	return (start);
}
