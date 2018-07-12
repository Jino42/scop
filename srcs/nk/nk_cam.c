#include "scop_nk.h"
#include "scop.h"

void				nk_cam_pitch_yaw(t_nk *nk, t_cam *cam)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_static(ctx, 25, 150, 2);
	nk_property_float(ctx, "Yaw", FLOAT_MIN, &cam->yaw, FLT_MAX, 0.1f, 0.05f);
	nk_property_float(ctx, "Pitch", FLT_MIN, &cam->pitch, FLT_MAX, 0.1f, 0.05f);
	cam->front = cam_get_front(cam->pitch, cam->yaw);
}

void				nk_cam_fov(t_nk *nk, t_cam *cam)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_labelf(ctx, NK_TEXT_LEFT, "FOV [%.2f]", cam->fov);
	nk_slider_float(ctx, 20.f, &cam->fov, 90.f, 0.1f);
}

void 				nk_cam(t_nk *nk, t_cam *cam)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Camera", NK_MAXIMIZED)) {

		nk_cam_fov(nk, cam);
		nk_position(nk, &cam->position);
		nk_cam_pitch_yaw(nk, cam);

		nk_tree_pop(ctx);
	}
}
