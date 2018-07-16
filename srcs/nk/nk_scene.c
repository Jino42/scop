#include "scop_nk.h"
#include "scop.h"

void				nk_scene_menu(t_nk *nk)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(120, 200)))
	{
		nk->state = (nk->menu_state == MENU_FILE) ? NK_MAXIMIZED: NK_MINIMIZED;
		if (nk_tree_state_push(ctx, NK_TREE_TAB, "FILE", &nk->state))
		{
			nk->menu_state = MENU_FILE;
			if (nk_menu_item_label(ctx, "New", NK_TEXT_LEFT))
			{
				nk->flag = 0;
				nk->flag |= POPUP_NEW;
				nk->popup = 1;
			}
			if (nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT))
			{
				nk->flag = 0;
				nk->flag |= POPUP_OPEN;
				nk->popup = 1;
			}
			nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT);
			if (nk_menu_item_label(ctx, "Save As", NK_TEXT_LEFT))
			{
				nk->flag = 0;
				nk->flag |= POPUP_SAVE_AS;
				nk->popup = 1;
			}
			nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT);
			nk_tree_pop(ctx);
		}
		else
			nk->menu_state = (nk->menu_state == MENU_FILE) ? MENU_NONE: nk->menu_state;
		nk_menu_end(ctx);
	}
}

void				nk_scene_menu_popup(t_nk *nk, t_scene *scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk->popup)
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "?", 0, nk_rect(WIDTH / 2 - 160, HEIGHT / 2 - 60, 330, 120)))
		{
			nk_layout_row_dynamic(ctx, 30, 1);
			if (nk->flag & POPUP_NEW)
				nk_label(ctx, "Ouvrir une nouvelle scène", NK_TEXT_CENTERED);
			if (nk->flag & POPUP_OPEN)
				nk_label(ctx, "Ouvrir une scène", NK_TEXT_CENTERED);
			if (nk->flag & POPUP_SAVE_AS)
				nk_label(ctx, "Enregistrer la scène en tant que", NK_TEXT_CENTERED);

			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk->flag & POPUP_NEW)
				nk_label(ctx, "Destination: ./json/", NK_TEXT_LEFT);
			if (nk->flag & POPUP_OPEN)
				nk_label(ctx, "Ouvrir:      ./json/", NK_TEXT_LEFT);
			if (nk->flag & POPUP_SAVE_AS)
				nk_label(ctx, "Destination: ./json/", NK_TEXT_LEFT);
			nk_edit_string(ctx, NK_EDIT_SIMPLE, &nk->buffer_text[7], &nk->len_text, 128, nk_filter_default);
			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_button_label(ctx, "OK")) {
				if (nk->flag & POPUP_SAVE_AS)
				{
					printf("%s\n", nk->buffer_text);
					if (scene_write(scene, nk->buffer_text))
						strcpy(nk->buffer[1], "Fichier enregistré !");
					else if (!scene_write(scene, nk->buffer_text))
						strcpy(nk->buffer[1], "Une erreur c'est produite.");
					nk->popup_over = 1;
				}
				nk->popup = 0;
				nk_popup_close(ctx);
			}
			if (nk_button_label(ctx, "Cancel")) {
				nk->popup = 0;
				nk_popup_close(ctx);
			}
			nk_popup_end(ctx);
		}
		else
			nk->popup = nk_false;
	}
}

void				nk_scene_menu_popup_over(t_nk *nk)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk->popup_over)
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "So", 0, nk_rect(WIDTH / 2 - 160, HEIGHT / 2 - 45, 330, 90)))
		{
			nk_layout_row_dynamic(ctx, 30, 1);
			nk_labelf(ctx, NK_TEXT_LEFT, "%s", nk->buffer[1]);
			if (nk_button_label(ctx, "Ok")) {
				nk->popup_over = 0;
				nk_popup_close(ctx);
			}
			nk_popup_end(ctx);
		}
		else
			nk->popup_over = nk_false;
	}
}

void				nk_scene(t_nk *nk, t_scene *scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_begin(ctx, "Scene", nk_rect(10, 10, 400, 800),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_menubar_begin(ctx);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 45);

		nk_scene_menu(nk);

		nk_scene_menu_popup(nk, scene);
		nk_scene_menu_popup_over(nk);


		nk_cam(nk, scene->cam);
		nk_m_model(nk, scene, scene->m_model);
		nk_m_shader(nk, scene->m_shader);
		nk_m_material(nk, scene->m_material);
		nk_m_light(nk, scene, scene->m_light);
	}
	nk_menubar_end(ctx);
	nk_end(ctx);
}
