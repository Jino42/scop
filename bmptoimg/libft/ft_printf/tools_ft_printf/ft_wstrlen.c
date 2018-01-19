/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:16:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_wstrlen(const wchar_t *str)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_wcharlen(str[i]);
		i++;
	}
	return (size);
}
