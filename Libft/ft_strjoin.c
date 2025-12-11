/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:09:35 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 08:30:31 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	char	*original;
	int		total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	string = malloc((total_len + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	original = string;
	while (*s1)
		*(string++) = *(s1++);
	while (*s2)
		*(string++) = *(s2++);
	*string = '\0';
	return (original);
}
