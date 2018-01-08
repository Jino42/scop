/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 18:14:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 20:25:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}

int			ft_ret_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}
