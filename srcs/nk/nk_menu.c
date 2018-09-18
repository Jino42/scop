/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 23:39:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:52:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

static void			nk_scene_menu_popup_over(t_nk *nk)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk->popup_over)
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "So", 0,
			nk_rect(WIDTH / 2 - 160, HEIGHT / 2 - 45, 330, 90)))
		{
			nk_layout_row_dynamic(ctx, 30, 1);
			nk_labelf(ctx, NK_TEXT_LEFT, "%s", nk->buffer[1]);
			if (nk_button_label(ctx, "Ok"))
			{
				nk->popup_over = 0;
				nk_popup_close(ctx);
			}
			nk_popup_end(ctx);
		}
		else
			nk->popup_over = nk_false;
	}
}

static void			nk_scene_menu_open(t_nk *nk, struct nk_context *ctx)
{
	nk->menu_state = MENU_FILE;
	if (nk_menu_item_label(ctx, "New", NK_TEXT_LEFT))
	{
		nk->flag = 0 | POPUP_NEW;
		nk->popup = 1;
	}
	if (nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT))
	{
		nk->flag = 0 | POPUP_OPEN;
		nk->popup = 1;
	}
	nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT);
	if (nk_menu_item_label(ctx, "Save As", NK_TEXT_LEFT))
	{
		nk->flag = 0 | POPUP_SAVE_AS;
		nk->popup = 1;
	}
	nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT);
	nk_tree_pop(ctx);
}

bool				nk_scene_menu(t_nk *nk, t_scene **scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(120, 200)))
	{
		nk->state = (nk->menu_state == MENU_FILE) ? NK_MAXIMIZED : NK_MINIMIZED;
		if (nk_tree_state_push(ctx, NK_TREE_TAB, "FILE", &nk->state))
			nk_scene_menu_open(nk, ctx);
		else
			nk->menu_state = (nk->menu_state == MENU_FILE)
								? MENU_NONE : nk->menu_state;
		nk_menu_end(ctx);
	}
	if (!(nk_scene_menu_popup(nk, scene, ctx)))
		return (false);
	nk_scene_menu_popup_over(nk);
	return (true);
}
