/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:21:29 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrbase(int n, int base)
{
	long long int	nb;
	int				reste;
	int				curr;

	reste = 0;
	curr = 0;
	nb = n;
	if (n < 0)
	{
		ft_putchar('-');
		nb = nb * -1;
	}
	reste = nb % base;
	curr = nb / base;
	if (curr != 0)
		ft_putnbrbase(curr, base);
	ft_putnbr(reste);
}
