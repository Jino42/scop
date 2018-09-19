/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:34:31 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:25:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	i = 0;
	p_s = (unsigned char*)s;
	while (n--)
	{
		if (p_s[i] == (unsigned char)c)
			return (&p_s[i]);
		i++;
	}
	return (NULL);
}
