/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:58:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:26:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_src;
	unsigned char	*p_dest;

	p_src = (unsigned char*)src;
	p_dest = (unsigned char*)dest;
	if (p_src < p_dest)
	{
		p_dest = p_dest + (n - 1);
		p_src = p_src + (n - 1);
		while (n--)
			*p_dest-- = *p_src--;
	}
	else
		while (n--)
			*p_dest++ = *p_src++;
	return (dest);
}
