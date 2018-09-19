/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sqrt_magnitude.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:35:52 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float		vector_sqrt_magnitude(const t_vector *vec)
{
	return (sqrtf(fabs((vec->x * vec->x)) +
					fabs((vec->y * vec->y)) +
					fabs((vec->z * vec->z))));
}
