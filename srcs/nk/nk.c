#include "scop_nk.h"
#include "scop.h"
/*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
/*nk_style_load_all_cursors(nk->, atlas->cursors);*/
/*nk_style_set_font(nk->, &droid->handle);*/
/*set_style(nk->, THEME_WHITE);*/
/*set_style(nk->, THEME_RED);*/
/*set_style(nk->, THEME_BLUE);*/
/*set_style(nk->, THEME_DARK);*/

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

t_nk				*nk_construct(GLFWwindow *win)
{
	t_nk *nk;

	if (!(nk = ft_memalloc(sizeof(t_nk))))
		return (NULL);
	nk->win = win;
	nk->ctx = nk_glfw3_init(nk->win, NK_GLFW3_INSTALL_CALLBACKS);
	nk_glfw3_font_stash_begin(&nk->atlas);
	nk_glfw3_font_stash_end();
	return (nk);
}

void				*nk_destruct(t_nk **nk)
{
	if (nk && *nk)
	{
		ft_memdel((void **)nk);
	}
	return (NULL);
}

void				nk_update(t_nk *nk)
{
	(void)nk;
	nk_glfw3_new_frame();

}
void				nk_render(t_nk *nk)
{
	(void)nk;
	nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

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
		sprintf(nk->buffer, "[%s]: %.2f, %.2f, %.2f", str, vector->x, vector->y,vector->z);
	else
		sprintf(nk->buffer, "%.2f, %.2f, %.2f", vector->x, vector->y,vector->z);
	if (nk_combo_begin_label(ctx, nk->buffer, nk_vec2(200,200)))
	{
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "#X:", FLOAT_MIN, &vector->x, FLOAT_MAX, 0.1,0.2f);
		nk_property_float(ctx, "#Y:", FLOAT_MIN, &vector->y, FLOAT_MAX, 0.1,0.2f);
		nk_property_float(ctx, "#Z:", FLOAT_MIN, &vector->z, FLOAT_MAX, 0.1,0.2f);
		nk_combo_end(ctx);
	}
}
