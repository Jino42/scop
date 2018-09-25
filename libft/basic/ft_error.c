/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 18:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 23:22:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_bool_error(char *string, bool (*func)(void *gen), void *gen)
{
	if (string)
	{
		ft_putstr(string);
		ft_putchar('\n');
	}
	if (func)
		return (func(gen));
	return (false);
}

void	*ft_error(char *string, void *(*func)(void *gen), void *gen)
{
	if (string)
	{
		ft_putstr(string);
		ft_putchar('\n');
	}
	if (func)
		return (func(gen));
	return (NULL);
}
