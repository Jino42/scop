#include "scop_nk.h"
#include "scop.h"

void 				nk_m_material(t_nk *nk, t_m_material *m_material)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Material", NK_MAXIMIZED))
	{
		nk_layout_row_static(ctx, 25, 150, 1);

		m_material->index_selected = nk_combo(ctx,
								(const char **)m_material->material_name,
								m_material->size,
								m_material->index_selected,
								25, nk_vec2(200,200));
		/*
		nk_model(nk, m_model->model[m_model->index_selected]);
		*/
		nk_tree_pop(ctx);
	}
}
