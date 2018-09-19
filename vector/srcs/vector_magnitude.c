/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:32:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:36:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float		vector_magnitude(const t_vector *vec)
{
	return (fabs((vec->x * vec->x)) +
				fabs((vec->y * vec->y)) +
				fabs((vec->z * vec->z)));
}
