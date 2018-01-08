/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_abs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:31:42 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:35:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_abs(const t_vector *a)
{
	t_vector new;

	vector_copy(&new, a);
	vector_abs(&new);
	return (new);
}

void			vector_abs(t_vector *a)
{
	if (a->x < 0)
		a->x *= -1;
	if (a->y < 0)
		a->y *= -1;
	if (a->z < 0)
		a->z *= -1;
	return ;
}
