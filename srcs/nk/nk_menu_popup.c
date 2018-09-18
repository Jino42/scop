/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_menu_popup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 23:52:39 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:52:40 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

static bool			nk_scene_menu_popup_ok(t_nk *nk,
											t_scene **scene,
											struct nk_context *ctx)
{
	if (nk->flag & POPUP_SAVE_AS)
	{
		if (scene_write((*scene), nk->buffer_text))
			strcpy(nk->buffer[1], "Fichier enregistré !");
		else if (!scene_write((*scene), nk->buffer_text))
			strcpy(nk->buffer[1], "Une erreur c'est produite.");
		nk->popup_over = 1;
	}
	else if (nk->flag & POPUP_OPEN)
		if (!scene_reload(scene, nk->buffer_text))
			return (false);
	nk->popup = 0;
	nk_popup_close(ctx);
	bzero(&nk->buffer_text[7], 255 - 7);
	return (true);
}

static void			nk_scene_menu_popup_text(t_nk *nk, struct nk_context *ctx)
{
	nk_layout_row_dynamic(ctx, 30, 1);
	if (nk->flag & POPUP_NEW)
		nk_label(ctx, "Ouvrir une nouvelle scène", NK_TEXT_CENTERED);
	if (nk->flag & POPUP_OPEN)
		nk_label(ctx, "Ouvrir une scène", NK_TEXT_CENTERED);
	if (nk->flag & POPUP_SAVE_AS)
	{
		nk_label(ctx, "Enregistrer la scène en tant que",
												NK_TEXT_CENTERED);
	}
	nk_layout_row_dynamic(ctx, 30, 2);
	if (nk->flag & POPUP_NEW)
		nk_label(ctx, "Destination: ./json/", NK_TEXT_LEFT);
	if (nk->flag & POPUP_OPEN)
		nk_label(ctx, "Ouvrir:      ./json/", NK_TEXT_LEFT);
	if (nk->flag & POPUP_SAVE_AS)
		nk_label(ctx, "Destination: ./json/", NK_TEXT_LEFT);
}

bool				nk_scene_menu_popup(t_nk *nk,
										t_scene **scene,
										struct nk_context *ctx)
{
	if (nk->popup)
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "?", 0,
			nk_rect(WIDTH / 2 - 160, HEIGHT / 2 - 60, 330, 120)))
		{
			nk_scene_menu_popup_text(nk, ctx);
			nk_edit_string(ctx, NK_EDIT_SIMPLE, &nk->buffer_text[7],
							&nk->len_text, 128, nk_filter_default);
			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_button_label(ctx, "OK"))
				if (!(nk_scene_menu_popup_ok(nk, scene, ctx)))
					return (false);
			if (nk_button_label(ctx, "Cancel"))
			{
				nk->popup = 0;
				nk_popup_close(ctx);
			}
			nk_popup_end(ctx);
		}
		else
			nk->popup = nk_false;
	}
	return (true);
}
