/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_lerp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:19 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:38:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_lerp(const t_vector *a, const t_vector *b, const float t)
{
	t_vector	new;
	float		clamp;

	clamp = t;
	if (t < 0)
		clamp = 0;
	if (t > 1)
		clamp = 1;
	new.x = a->x + (b->x - a->x) * clamp;
	new.y = a->y + (b->y - a->y) * clamp;
	new.z = a->z + (b->z - a->z) * clamp;
	return (new);
}

t_vector		vector_lerp_unclamped(const t_vector *a,
											const t_vector *b, const float t)
{
	t_vector new;

	new.x = a->x + (b->x - a->x) * t;
	new.y = a->y + (b->y - a->y) * t;
	new.z = a->z + (b->z - a->z) * t;
	return (new);
}
