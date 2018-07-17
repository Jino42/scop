#include "scop.h"
#include "scop_nk.h"


void 				nk_light(t_nk *nk, t_light *light)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	nk_layout_row_static(ctx, 30, 300, 1);
	nk_combo_vector(nk, &light->position, "Position");
	nk_layout_row_static(ctx, 30, 150, 2);
	nk_combo_colorf(nk, &light->diffuse, "Diffuse");
	nk_combo_colorf(nk, &light->ambient, "Ambient");
	nk_combo_colorf(nk, &light->specular, "Specular");
}
