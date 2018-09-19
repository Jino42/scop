/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:09:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:28:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(&s[start]) < len)
		return (NULL);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (s[start] && len)
	{
		str[i] = s[start];
		start++;
		len--;
		i++;
	}
	str[i] = '\0';
	return (str);
}
