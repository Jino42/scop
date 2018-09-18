/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_widget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:23:45 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/18 23:54:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

void				nk_position(t_nk *nk, t_vector *vector)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	nk_layout_row_push(ctx, 60);
	nk_label(ctx, "Position", NK_TEXT_LEFT);
	nk_layout_row_push(ctx, 90);
	nk_property_float(ctx, "X:", FLOAT_MIN, &vector->x, FLT_MAX, 0.1f, 0.2f);
	nk_layout_row_push(ctx, 90);
	nk_property_float(ctx, "Y:", FLOAT_MIN, &vector->y, FLT_MAX, 0.1f, 0.2f);
	nk_layout_row_push(ctx, 90);
	nk_property_float(ctx, "Z:", FLOAT_MIN, &vector->z, FLT_MAX, 0.1f, 0.2f);
	nk_layout_row_end(ctx);
}

void				nk_combo_vector(t_nk *nk, t_vector *vector, const char *str)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (str)
		sprintf(nk->buffer[0], "[%s]: %.2f, %.2f, %.2f",
			str, vector->x, vector->y, vector->z);
	else
		sprintf(nk->buffer[0], "%.2f, %.2f, %.2f",
			vector->x, vector->y, vector->z);
	if (nk_combo_begin_label(ctx, nk->buffer[0], nk_vec2(200, 200)))
	{
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "#X:", FLOAT_MIN, &vector->x,
							FLOAT_MAX, 0.1, 0.2f);
		nk_property_float(ctx, "#Y:", FLOAT_MIN, &vector->y,
							FLOAT_MAX, 0.1, 0.2f);
		nk_property_float(ctx, "#Z:", FLOAT_MIN, &vector->z,
							FLOAT_MAX, 0.1, 0.2f);
		nk_combo_end(ctx);
	}
}

void				nk_check(t_nk *nk,
								int *flag,
								const int define,
								const char *str)
{
	int					check;
	struct nk_context	*ctx;

	ctx = nk->ctx;
	check = (*flag & define);
	nk_checkbox_label(ctx, str, &check);
	if (!check)
	{
		if ((*flag) & define)
			(*flag) ^= define;
	}
	else
		(*flag) |= define;
}
