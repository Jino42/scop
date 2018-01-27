/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:46:41 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/01/27 16:37:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_material			*material_construct_tab()
{
	t_material	*material;

	if (!(material = ft_memalloc(sizeof(t_material) * NB_MAT)))
		return (NULL);
	material[F_MAT_EMERALD] = MAT_EMERALD;
	material[F_MAT_PEARL] = MAT_PEARL;
	material[F_MAT_JADE] = MAT_JADE;
	material[F_MAT_RED_PLASTIC] = MAT_RED_PLASTIC;
	return (material);
}

t_material		*material_construct()
{
	t_material *material;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	*material = MAT_PR;
	return (material);
}

void			*material_destruct(t_material **material)
{
	ft_memdel((void *)material);
	return (NULL);
}
