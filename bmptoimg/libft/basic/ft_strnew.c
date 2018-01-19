/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:10:52 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:28:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)ft_memalloc(sizeof(*str) * (size + 1))))
		return (NULL);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
