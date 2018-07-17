#include "scop_nk.h"
#include "scop.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

# define THEME_RED (1 << 0)

static void set_style(struct nk_context *ctx, int theme)
{
    struct nk_color table[NK_COLOR_COUNT];
	if (theme == THEME_RED)
	{
        table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
        table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
        table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
        table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
        table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
        table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
        table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
        table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
        table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
        table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
        table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
        table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
        table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
        table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
        table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
        table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
        nk_style_from_table(ctx, table);
    }
	else
	{
        nk_style_default(ctx);
    }
}


t_nk				*nk_construct(GLFWwindow *win)
{
	t_nk *nk;

	if (!(nk = ft_memalloc(sizeof(t_nk))))
		return (NULL);
	nk->win = win;
	nk->ctx = nk_glfw3_init(nk->win, NK_GLFW3_INSTALL_CALLBACKS);
	nk_glfw3_font_stash_begin(&nk->atlas);
	nk_glfw3_font_stash_end();
	set_style(nk->ctx, THEME_RED);
	strcpy(nk->buffer_text, "./json/");
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
		sprintf(nk->buffer[0], "[%s]: %.2f, %.2f, %.2f", str, vector->x, vector->y,vector->z);
	else
		sprintf(nk->buffer[0], "%.2f, %.2f, %.2f", vector->x, vector->y,vector->z);
	if (nk_combo_begin_label(ctx, nk->buffer[0], nk_vec2(200,200)))
	{
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "#X:", FLOAT_MIN, &vector->x, FLOAT_MAX, 0.1,0.2f);
		nk_property_float(ctx, "#Y:", FLOAT_MIN, &vector->y, FLOAT_MAX, 0.1,0.2f);
		nk_property_float(ctx, "#Z:", FLOAT_MIN, &vector->z, FLOAT_MAX, 0.1,0.2f);
		nk_combo_end(ctx);
	}
}

void				nk_combo_colorf(t_nk *nk, t_vector *vec, const char *str)
{
	struct nk_context		*ctx;
	struct nk_colorf		*colorf;

	ctx = nk->ctx;
	colorf = (struct nk_colorf *)vec;
	nk_label(ctx, str, NK_TEXT_LEFT);
	if (nk_combo_begin_color(ctx, nk_rgb_cf(*colorf), nk_vec2(200,400)))
	{
		nk_layout_row_dynamic(ctx, 120, 1);
		*colorf = nk_color_picker(ctx, *colorf, NK_RGBA);

		nk_layout_row_dynamic(ctx, 25, 2);
		if (nk_option_label(ctx, "RGB", nk->flag & COLOR_MODE_RGBA))
		{
			if (nk->flag & COLOR_MODE_HSV)
				nk->flag ^= COLOR_MODE_HSV;
			nk->flag |= COLOR_MODE_RGBA;

		}
		if (nk_option_label(ctx, "HSV", nk->flag & COLOR_MODE_HSV))
		{
			if (nk->flag & COLOR_MODE_RGBA)
				nk->flag ^= COLOR_MODE_RGBA;
			nk->flag |= COLOR_MODE_HSV;
		}

		nk_layout_row_dynamic(ctx, 25, 1);
		if (nk->flag & COLOR_MODE_RGBA) {
			colorf->r = nk_propertyf(ctx, "#R:", 0, colorf->r, 1.0f, 0.01f,0.005f);
			colorf->g = nk_propertyf(ctx, "#G:", 0, colorf->g, 1.0f, 0.01f,0.005f);
			colorf->b = nk_propertyf(ctx, "#B:", 0, colorf->b, 1.0f, 0.01f,0.005f);
			colorf->a = nk_propertyf(ctx, "#A:", 0, colorf->a, 1.0f, 0.01f,0.005f);
		} else {
			float hsva[4];
			nk_colorf_hsva_fv(hsva, *colorf);
			hsva[0] = nk_propertyf(ctx, "#H:", 0, hsva[0], 1.0f, 0.01f,0.05f);
			hsva[1] = nk_propertyf(ctx, "#S:", 0, hsva[1], 1.0f, 0.01f,0.05f);
			hsva[2] = nk_propertyf(ctx, "#V:", 0, hsva[2], 1.0f, 0.01f,0.05f);
			hsva[3] = nk_propertyf(ctx, "#A:", 0, hsva[3], 1.0f, 0.01f,0.05f);
			*colorf = nk_hsva_colorfv(hsva);
		}
		nk_combo_end(ctx);
	}
}
