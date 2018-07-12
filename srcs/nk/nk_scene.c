#include "scop_nk.h"
#include "scop.h"

void				nk_scene(t_nk *nk, t_scene *scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_begin(ctx, "Scene", nk_rect(10, 10, 400, 600),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_menubar_begin(ctx);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 45);
		if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(120, 200)))
		{
			nk->state = (nk->menu_state == MENU_FILE) ? NK_MAXIMIZED: NK_MINIMIZED;
			if (nk_tree_state_push(ctx, NK_TREE_TAB, "FILE", &nk->state))
			{
				nk->menu_state = MENU_FILE;
				nk_menu_item_label(ctx, "New", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Save As", NK_TEXT_LEFT);
				nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT);
				nk_tree_pop(ctx);
			}
			else
				nk->menu_state = (nk->menu_state == MENU_FILE) ? MENU_NONE: nk->menu_state;
			nk_menu_end(ctx);
		}
		nk_cam(nk, scene->cam);
		nk_m_model(nk, scene->m_model);
		nk_m_shader(nk, scene->m_shader);
	}
	nk_menubar_end(ctx);
	nk_end(ctx);
}
