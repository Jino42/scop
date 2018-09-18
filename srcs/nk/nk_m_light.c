/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_m_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:34:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 22:35:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

void				nk_m_light(t_nk *nk, t_scene *scene, t_m_light *m_light)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Light", NK_MAXIMIZED))
	{
		nk_layout_row_static(ctx, 25, 150, 1);
		m_light->index_selected = nk_combo(ctx,
								(const char **)m_light->light_name,
								m_light->size,
								m_light->index_selected,
								25, nk_vec2(200, 200));
		scene->index_light = m_light->index_selected;
		nk_light(nk, m_light->light[m_light->index_selected]);
		nk_tree_pop(ctx);
	}
}
