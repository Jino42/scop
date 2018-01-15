/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:46:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:48:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void 	matrix_print(const t_matrix *m, const char *str)
{
	int y;
	int x;

	printf("Print %s :\n", str);
	y = 0;
	while (y < 4)
	{
		x = 0;
		printf("[");
		while(x < 4)
		{
			printf("%.2f ", m->matrix[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
}
