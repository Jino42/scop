/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 23:06:05 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:28:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t t;

	i = 0;
	t = 0;
	while (dest[i])
		i++;
	while (src[t] && n)
	{
		dest[i + t] = src[t];
		t++;
		n--;
	}
	dest[i + t] = '\0';
	return (dest);
}
