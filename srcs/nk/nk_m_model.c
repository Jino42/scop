/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_m_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:35:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 22:35:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

void				nk_m_model(t_nk *nk, t_scene *scene, t_m_model *m_model)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Model", NK_MAXIMIZED))
	{
		nk_layout_row_static(ctx, 25, 150, 1);
		m_model->index_selected = nk_combo(ctx,
								(const char **)m_model->model_name,
								m_model->size,
								m_model->index_selected,
								25, nk_vec2(200, 200));
		nk_model(nk, scene, m_model->model[m_model->index_selected]);
		nk_tree_pop(ctx);
	}
}
