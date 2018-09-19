/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:21:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/13 21:23:42 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_offset(void *dest, const void *src, size_t offset, size_t n)
{
	unsigned char	*p_src;
	unsigned char	*p_dest;
	size_t			i;

	if (n == 0 || !src || !dest)
		return (dest);
	i = 0;
	p_dest = (unsigned char*)dest;
	p_src = (unsigned char*)src;
	while (i < n)
	{
		p_dest[offset + i] = p_src[i];
		i++;
	}
	return (dest);
}
