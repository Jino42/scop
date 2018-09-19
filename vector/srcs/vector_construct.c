/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_construct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:31:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/25 17:12:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector		vector_construct(const float x, const float y, const float z)
{
	t_vector new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = 1.f;
	return (new);
}
