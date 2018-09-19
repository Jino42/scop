/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:37:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_floor(const t_vector *a)
{
	t_vector new;

	new.x = (int)a->x;
	new.y = (int)a->y;
	new.z = (int)a->z;
	return (new);
}

void			vector_floor(t_vector *a)
{
	a->x = (int)a->x;
	a->y = (int)a->y;
	a->z = (int)a->z;
	return ;
}
