#include "scop.h"
#include "scop_nk.h"


void 				nk_light(t_nk *nk, t_light *light)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_static(ctx, 30, 300, 1);
	if (light->flag & LIGHT_BASIC || light->flag & LIGHT_POINT)
		nk_combo_vector(nk, &light->position, "Position");
	else if (light->flag & LIGHT_DIRECTIONNAL)
		nk_combo_vector(nk, &light->rotation, "Direction");
	nk_layout_row_static(ctx, 30, 150, 2);
	nk_combo_colorf(nk, &light->diffuse, "Diffuse");
	nk_combo_colorf(nk, &light->ambient, "Ambient");
	nk_combo_colorf(nk, &light->specular, "Specular");
	nk_layout_row_static(ctx, 30, 80, 3);
	light->flag = nk_option_label(ctx, "Basic", light->flag & LIGHT_BASIC)           ? LIGHT_BASIC         : light->flag;
	light->flag = nk_option_label(ctx, "Direc.",  light->flag & LIGHT_DIRECTIONNAL)  ? LIGHT_DIRECTIONNAL  : light->flag;
	light->flag = nk_option_label(ctx, "Point",  light->flag & LIGHT_POINT)          ? LIGHT_POINT         : light->flag;
	if (light->flag & LIGHT_POINT)
	{
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Constent", 0.0001f, &light->constent, 1000.f, 0.05f, 0.05f);
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Linear", 0.0001f, &light->linear, 1.f, 0.005f, 0.005f);
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Quadratic", 0.0001f, &light->quadratic, 1.f, 0.0005f, 0.0005f);
	}
	light->update = true;
}
