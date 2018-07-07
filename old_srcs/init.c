/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:55:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/08 21:49:00 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		flag(int64_t *f, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-void"))
			*f |= 0;
		else
			return (i);
		i++;
	}
	return (i);
}
