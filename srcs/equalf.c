/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:10:21 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:10:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

bool	equalf(const float a, const float b)
{
	if (fabs(a - b) < 0.00005f)
		return (true);
	return (false);
}

bool	equal3f(const float *a, const float *b)
{
	if (equalf(a[0], b[0]) && equalf(a[1], b[1]) && equalf(a[2], b[2]))
		return (true);
	return (false);
}

bool	equal2f(const float *a, const float *b)
{
	if (equalf(a[0], b[0]) && equalf(a[1], b[1]))
		return (true);
	return (false);
}
