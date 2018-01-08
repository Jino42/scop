/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizebit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:17:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_sizebit(long long nbr)
{
	int		size;

	size = 0;
	while (nbr != 0)
	{
		nbr = nbr >> 1;
		size++;
	}
	return (size);
}
