/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:27:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_size_wstr(const wchar_t *str, size_t len)
{
	size_t i;
	size_t size;

	size = 0;
	i = 0;
	while (str[i])
	{
		size += ft_wcharlen(str[i]);
		if (size > len)
			return (i);
		i++;
	}
	return (i);
}

wchar_t			*ft_wstrsub(const wchar_t *s, unsigned int start, size_t len)
{
	wchar_t		*str;
	size_t		i;
	size_t		size;

	size = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_wstrlen(&s[start]) < len)
		return (NULL);
	str = ft_wstrnew(ft_size_wstr(&s[start], len));
	if (str == NULL)
		return (NULL);
	size += ft_wcharlen(s[start]);
	while (s[start] && size <= len)
	{
		str[i] = s[start];
		start++;
		size += ft_wcharlen(s[start]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
