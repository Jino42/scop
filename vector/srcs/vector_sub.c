/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:35:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_sub(const t_vector *a, const t_vector *b)
{
	t_vector new;

	new.x = a->x - b->x;
	new.y = a->y - b->y;
	new.z = a->z - b->z;
	return (new);
}

void			vector_sub(t_vector *a, const t_vector *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return ;
}
