/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:07 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:38:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vector_distance(const t_vector *a, const t_vector *b)
{
	t_vector new;

	new.x = a->x - b->x;
	new.y = a->y - b->y;
	new.z = a->z - b->z;
	return (vector_sqrt_magnitude(&new));
}
