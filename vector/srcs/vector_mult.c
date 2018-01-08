/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:36:16 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_mult(const t_vector *a, const float mult)
{
	t_vector new;

	new.x = a->x * mult;
	new.y = a->y * mult;
	new.z = a->z * mult;
	return (new);
}

void			vector_mult(t_vector *a, const float mult)
{
	a->x *= mult;
	a->y *= mult;
	a->z *= mult;
	return ;
}
