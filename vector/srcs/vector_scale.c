/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:35:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_scale(const t_vector *a, const t_vector *b)
{
	t_vector new;

	new.x = a->x * b->x;
	new.y = a->y * b->y;
	new.z = a->z * b->z;
	return (new);
}

void			vector_scale(t_vector *a, const t_vector *b)
{
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
	return ;
}
