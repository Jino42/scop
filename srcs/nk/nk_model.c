#include "scop_nk.h"
#include "scop.h"

void 				nk_model(t_nk *nk, t_m_model *m_model)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_tree_push(ctx, NK_TREE_TAB, "Model", NK_MINIMIZED)) {
		(void)m_model;
		static int selected[4] = {nk_false, nk_false, nk_true, nk_false};

		nk_layout_row_static(ctx, 18, 100, 1);
		nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[0]);
		nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[1]);
		nk_label(ctx, "Not Selectable", NK_TEXT_LEFT);
		nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[2]);
		nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[3]);

		nk_tree_pop(ctx);
	}
}
