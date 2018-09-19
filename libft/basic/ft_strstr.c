/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 22:03:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:28:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int size;
	int count;

	size = ft_strlen(little);
	i = 0;
	count = 0;
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i] != '\0')
	{
		while (big[i + count] == little[count])
		{
			count++;
			if (count == size)
				return ((char*)big + i);
		}
		count = 0;
		i++;
	}
	return (NULL);
}
