/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:12:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 16:12:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_material		*material_construct(char *name)
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	material->name = strdup(name);
	return (material);
}

void			*material_destruct(t_material **material)
{
	if (material && *material)
	{
		ft_memdel((void **)(&(*material)->name));
		ft_memdel((void **)material);
	}
	return (NULL);
}
