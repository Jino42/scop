/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:48:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 00:19:53 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_light		*light_construct(char *name)
{
	t_light *light;

	if (!(light = ft_memalloc(sizeof(t_light))))
		return (NULL);
	light->update = true;
	light->name = strdup(name);
	light->intensity = 1.f;
	return (light);
}

void		*light_destruct(t_light **light)
{
	if (light && *light)
	{
		ft_memdel((void **)(&(*light)->name));
		ft_memdel((void **)light);
	}
	return (NULL);
}
