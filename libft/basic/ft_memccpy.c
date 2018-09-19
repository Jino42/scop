/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:14:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:25:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const char	*p_src;
	char		*p_dest;
	size_t		i;

	if (n == 0)
		return (NULL);
	i = 0;
	p_dest = (char*)dest;
	p_src = (const char*)src;
	while (p_src[i] != c && i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	if (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
		return ((void*)&p_dest[i]);
	}
	else
		return (NULL);
}
