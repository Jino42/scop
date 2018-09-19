/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:37:12 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:40:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	matrix_transpose(t_matrix *mn)
{
	t_matrix	m;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			m.matrix[x][y] = mn->matrix[y][x];
			x++;
		}
		y++;
	}
	*mn = m;
}

t_matrix	matrix_get_transpose(t_matrix *mn)
{
	t_matrix	m;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			m.matrix[x][y] = mn->matrix[y][x];
			x++;
		}
		y++;
	}
	return (m);
}
