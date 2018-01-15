/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:49:47 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/15 20:50:37 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float		get_radians(const float degrees)
{
	return ((degrees * M_PI) / 180.f);
}

float		get_degrees(const float radians)
{
	return (radians * 180 / M_PI);
}
