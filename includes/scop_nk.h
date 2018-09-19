#ifndef SCOP_NK_H
# define SCOP_NK_H

# include "glad.h"
# include "nuk_glfw_gl3.h"
# include "libft.h"
# include "cJSON.h"
# include <stdbool.h>
# include "vector.h"
# include <float.h>

# define MAX_VERTEX_BUFFER 512 * 1024
# define MAX_ELEMENT_BUFFER 128 * 1024

# define THEME_RED (1 << 0)

# define MENU_NONE (1 << 0)
# define MENU_FILE (1 << 1)

# define POPUP_NEW (1 << 2)
# define POPUP_SAVE_AS (1 << 3)
# define POPUP_OPEN (1 << 4)
# define COLOR_MODE_RGBA (1 << 5)
# define COLOR_MODE_HSV (1 << 6)

typedef struct		s_nk
{
	GLFWwindow				*win;
	struct nk_context		*ctx;
	struct nk_context		*ctx_camera;
	struct nk_colorf		bg;
	struct nk_font_atlas	*atlas;
	int						width;
	int						height;
	int						menu_state;
	enum nk_collapse_states	state;
	char					buffer[5][256];
	char					buffer_text[256];
	int						len_text;
	int						popup;
	int						popup_over;
	int						flag;
}					t_nk;

t_nk				*nk_construct(GLFWwindow *win);
void				*nk_destruct(t_nk **nk);
void				set_style(struct nk_context *ctx, int theme);
void				nk_example(t_nk *nk);
void				nk_update(t_nk *nk);
void				nk_render(t_nk *nk);
void				nk_position(t_nk *nk, t_vector *vector);
void				nk_combo_vector(t_nk *nk, t_vector *vector, const char *str);
void				nk_combo_colorf(t_nk *nk, t_vector *vec, const char *str);
void				nk_check(t_nk *nk, int *flag, const int define, const char *str);

#endif
