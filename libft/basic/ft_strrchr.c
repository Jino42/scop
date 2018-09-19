/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 22:58:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:28:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = NULL;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			p = (char*)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		return ((char*)&s[i]);
	else
		return (p);
}
