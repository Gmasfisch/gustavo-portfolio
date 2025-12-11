/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:11:17 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 11:34:36 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*dest;
	char	*destcpy;
	int		length;

	length = ft_strlen(s);
	ptr = (char *) s;
	dest = malloc((length + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	destcpy = dest;
	while (*ptr)
		*(dest++) = *(ptr++);
	*dest = '\0';
	return (destcpy);
}
