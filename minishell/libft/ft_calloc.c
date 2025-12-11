/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemoula <mlemoula@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:24:43 by mlemoula          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:00 by mlemoula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*memory;

	memory = (void *)malloc(nmemb * size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, nmemb * size);
	return (memory);
}
