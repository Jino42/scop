/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 18:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 18:14:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_bool_error(char *string, bool (*func)(void *gen), void *gen)
{
	if (string)
	{
		ft_putstr_fd(string, 2);
		ft_putchar_fd('\n', 2);
	}
	if (func)
		return (func(gen));
	return (false);
}

void	*ft_error(char *string, void *(*func)(void *gen), void *gen)
{
	if (string)
	{
		ft_putstr_fd(string, 2);
		ft_putchar_fd('\n', 2);
	}
	if (func)
		return (func(gen));
	return (NULL);
}
