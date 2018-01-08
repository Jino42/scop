/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:02 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:36:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_copy(const t_vector *a)
{
	t_vector new;

	new.x = a->x;
	new.y = a->y;
	new.z = a->z;
	return (new);
}

void			vector_copy(t_vector *a, const t_vector *b)
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}
