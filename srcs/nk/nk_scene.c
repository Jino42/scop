/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 23:39:32 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:40:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

bool				nk_scene(t_nk *nk, t_scene **scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_begin(ctx, "Scene", nk_rect(10, 10, 400, 1200),
		NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_menubar_begin(ctx);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 45);
		if (!(nk_scene_menu(nk, scene)))
			return (false);
		nk_cam(nk, (*scene)->cam);
		nk_m_model(nk, (*scene), (*scene)->m_model);
		nk_m_material(nk, (*scene)->m_material);
		nk_m_light(nk, (*scene), (*scene)->m_light);
	}
	nk_menubar_end(ctx);
	nk_end(ctx);
	return (true);
}
