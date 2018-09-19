/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:14:23 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(wchar_t c)
{
	int size;
	int i;

	i = 0;
	size = ft_sizebit(c);
	i++;
	if (size > 7)
		i++;
	if (size > 11)
		i++;
	if (size > 16)
		i++;
	return (i);
}
