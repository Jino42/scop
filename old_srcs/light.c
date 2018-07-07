/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 14:25:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/27 14:51:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_light		*light_construct()
{
	t_light	*light;
	if (!(light = ft_memalloc(sizeof(t_light))))
		return (NULL);
	light->ambient = vector_construct(0.9f, 0.9f, 0.9f);
	light->diffuse = vector_construct(0.70f, 0.70f, 0.70f);
	light->specular = vector_construct(1.f, 1.f, 1.f);
	light->position = vector_construct(0.3f, 0.3f, 0.3f);
	return (light);
}

void		*light_destruct(t_light **light)
{
	ft_memdel((void *)light);
	return (NULL);
}
