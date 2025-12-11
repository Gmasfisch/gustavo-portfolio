/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfischba <gfischba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:01:49 by gfischba          #+#    #+#             */
/*   Updated: 2024/11/21 18:30:40 by gfischba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == 0)
		return ((char *) big);
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while (big [i + j] == little[j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char *) big + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

/*int main(void)
{
	char *little = "lorem ipsum dolor sit amet";
	char *other = "ipsumm";
	
	char *test = ft_strnstr(little, other, 30);
	printf("%s", test);

}*/
