/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:28:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/17 14:07:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

void				nk_cam_pitch_yaw(t_nk *nk, t_cam *cam)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_static(ctx, 25, 150, 2);
	cam->front = cam_get_front(cam->pitch, cam->yaw);
}

void				nk_cam(t_nk *nk, t_cam *cam)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Camera", NK_MAXIMIZED))
	{
		nk_position(nk, &cam->position);
		nk_cam_pitch_yaw(nk, cam);
		nk_tree_pop(ctx);
	}
}
