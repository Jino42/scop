/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:38:25 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 22:38:50 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "scop_nk.h"

void				nk_material(t_nk *nk, t_material *material)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_static(ctx, 30, 150, 2);
	nk_combo_colorf(nk, &material->diffuse, "Diffuse");
	nk_combo_colorf(nk, &material->ambient, "Ambient");
	nk_combo_colorf(nk, &material->specular, "Specular");
	nk_layout_row_static(ctx, 25, 300, 1);
	nk_property_float(ctx, "Shininess", 0.1f, &material->shininess,
					FLT_MAX, 0.5f, 0.2f);
}
