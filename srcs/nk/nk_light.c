#include "scop.h"
#include "scop_nk.h"


void 				nk_light(t_nk *nk, t_light *light)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_dynamic(ctx, 30, 2);
	nk_labelf(ctx, NK_TEXT_LEFT, "Intensity [%.2f]", light->intensity);
	nk_slider_float(ctx, 0.f, &light->intensity, 1.f, 0.01f);
	nk_layout_row_static(ctx, 30, 300, 1);
	nk_combo_vector(nk, &light->position, "Position");
	nk_layout_row_static(ctx, 30, 300, 1);
	nk_combo_vector(nk, &light->rotation, "Direction");
	nk_layout_row_static(ctx, 30, 150, 2);
	nk_combo_colorf(nk, &light->diffuse, "Diffuse");
	nk_combo_colorf(nk, &light->ambient, "Ambient");
	nk_combo_colorf(nk, &light->specular, "Specular");
	nk_layout_row_static(ctx, 30, 80, 3);
	light->flag = nk_option_label(ctx, "Basic", light->flag & LIGHT_BASIC)           ? LIGHT_BASIC         : light->flag;
	light->flag = nk_option_label(ctx, "Direc.",  light->flag & LIGHT_DIRECTIONNAL)  ? LIGHT_DIRECTIONNAL  : light->flag;
	light->flag = nk_option_label(ctx, "Point",  light->flag & LIGHT_POINT)          ? LIGHT_POINT         : light->flag;
	light->flag = nk_option_label(ctx, "Spot",  light->flag & LIGHT_SPOT)            ? LIGHT_SPOT          : light->flag;
	if (light->flag & LIGHT_POINT)
	{
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Constent", 0.0001f, &light->constent, 1000.f, 0.05f, 0.05f);
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Linear", 0.0001f, &light->linear, 1.f, 0.005f, 0.005f);
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Quadratic", 0.0001f, &light->quadratic, 1.f, 0.0005f, 0.0005f);
	}
	if (light->flag & LIGHT_SPOT)
	{
		nk_layout_row_static(ctx, 30, 300, 1);
		nk_property_float(ctx, "Angle", 0.0001f, &light->spot_little_radius, 360.f, 0.05f, 0.05f);
		nk_property_float(ctx, "Angle5", 0.0001f, &light->spot_big_radius, 360.f, 0.05f, 0.05f);
	}
	light->update = true;
}
