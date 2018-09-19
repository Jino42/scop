/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:10 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:36:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_get_div(const t_vector *a, const float div)
{
	t_vector new;

	new.x = a->x / div;
	new.y = a->y / div;
	new.z = a->z / div;
	return (new);
}

void			vector_div(t_vector *a, const float div)
{
	a->x /= div;
	a->y /= div;
	a->z /= div;
	return ;
}
