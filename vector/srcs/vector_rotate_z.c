/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate_z.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:44 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:39:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void		vector_rotate_z(t_vector *a, const float angle)
{
	float tmp;

	tmp = a->x * cos(angle) - a->y * sin(angle);
	a->y = a->x * sin(angle) + a->y * cos(angle);
	a->x = tmp;
	return ;
}

t_vector	vector_get_rotate_z(const t_vector *a, const float angle)
{
	t_vector new;

	new.x = a->x * cos(angle) - a->y * sin(angle);
	new.y = a->x * sin(angle) + a->y * cos(angle);
	new.z = a->z;
	return (new);
}
