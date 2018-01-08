/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross_product.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:32:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void		vector_cross_product(t_vector *a, const t_vector *b)
{
	t_vector new;

	new.x = (a->y * b->z) - (a->z * b->y);
	new.y = (a->z * b->x) - (a->x * b->z);
	new.z = (a->x * b->y) - (a->y * b->x);
	*a = new;
	return ;
}

t_vector	vector_get_cross_product(const t_vector *a, const t_vector *b)
{
	t_vector new;

	new.x = (a->y * b->z) - (a->z * b->y);
	new.y = (a->z * b->x) - (a->x * b->z);
	new.z = (a->x * b->y) - (a->y * b->x);
	return (new);
}
