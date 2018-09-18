/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_widget_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 23:54:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:57:36 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

static void			nk_combo_colorf_option(t_nk *nk, struct nk_context *ctx)
{
	nk_layout_row_dynamic(ctx, 25, 2);
	if (nk_option_label(ctx, "RGB", nk->flag & COLOR_MODE_RGBA))
	{
		if (nk->flag & COLOR_MODE_HSV)
			nk->flag ^= COLOR_MODE_HSV;
		nk->flag |= COLOR_MODE_RGBA;
	}
	if (nk_option_label(ctx, "HSV", nk->flag & COLOR_MODE_HSV))
	{
		if (nk->flag & COLOR_MODE_RGBA)
			nk->flag ^= COLOR_MODE_RGBA;
		nk->flag |= COLOR_MODE_HSV;
	}
}

static void			nk_combo_colorf_print_value(t_nk *nk,
												struct nk_context *ctx,
												struct nk_colorf *colorf)
{
	float					hsva[4];

	if (nk->flag & COLOR_MODE_RGBA)
	{
		colorf->r = nk_propertyf(ctx, "#R:", 0, colorf->r,
									1.0f, 0.01f, 0.005f);
		colorf->g = nk_propertyf(ctx, "#G:", 0, colorf->g,
									1.0f, 0.01f, 0.005f);
		colorf->b = nk_propertyf(ctx, "#B:", 0, colorf->b,
									1.0f, 0.01f, 0.005f);
		colorf->a = nk_propertyf(ctx, "#A:", 0, colorf->a,
									1.0f, 0.01f, 0.005f);
	}
	else
	{
		nk_colorf_hsva_fv(hsva, *colorf);
		hsva[0] = nk_propertyf(ctx, "#H:", 0, hsva[0], 1.0f, 0.01f, 0.05f);
		hsva[1] = nk_propertyf(ctx, "#S:", 0, hsva[1], 1.0f, 0.01f, 0.05f);
		hsva[2] = nk_propertyf(ctx, "#V:", 0, hsva[2], 1.0f, 0.01f, 0.05f);
		hsva[3] = nk_propertyf(ctx, "#A:", 0, hsva[3], 1.0f, 0.01f, 0.05f);
		*colorf = nk_hsva_colorfv(hsva);
	}
}

void				nk_combo_colorf(t_nk *nk, t_vector *vec, const char *str)
{
	struct nk_context		*ctx;
	struct nk_colorf		*colorf;

	ctx = nk->ctx;
	colorf = (struct nk_colorf *)vec;
	nk_label(ctx, str, NK_TEXT_LEFT);
	if (nk_combo_begin_color(ctx, nk_rgb_cf(*colorf), nk_vec2(200, 400)))
	{
		nk_layout_row_dynamic(ctx, 120, 1);
		*colorf = nk_color_picker(ctx, *colorf, NK_RGBA);
		nk_combo_colorf_option(nk, ctx);
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_combo_colorf_print_value(nk, ctx, colorf);
		nk_combo_end(ctx);
	}
}
