/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:32:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void		vector_limit(t_vector *a, const float limit)
{
	if (vector_magnitude(a) > limit)
	{
		vector_normalize(a);
		a->x *= limit;
		a->y *= limit;
		a->z *= limit;
	}
	return ;
}
