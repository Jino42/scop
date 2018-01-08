/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_aequals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:31:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/12/10 22:31:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

bool		vector_aequals(const t_vector *a, const t_vector *b)
{
	if (fabs(vector_sqrt_magnitude(a) - vector_sqrt_magnitude(b)) < 0.00005)
		return (true);
	return (false);
}
