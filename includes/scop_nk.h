#ifndef SCOP_NK_H
# define SCOP_NK_H

# include <stdbool.h>
# include "glad.h"
# include "scop_glfw.h"
# include "libft.h"
# include "scop.h"
#include <float.h>
//# include "nuklear_glfw_gl3.h"
//# include "nuk_glfw_gl3.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include "nuk_head.h"
#include <glfw3.h>

enum nk_glfw_init_state{
    NK_GLFW3_DEFAULT=0,
    NK_GLFW3_INSTALL_CALLBACKS
};

NK_API struct nk_context*   nk_glfw3_init(GLFWwindow *win, enum nk_glfw_init_state);
NK_API void                 nk_glfw3_shutdown(void);
NK_API void                 nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas);
NK_API void                 nk_glfw3_font_stash_end(void);
NK_API void                 nk_glfw3_new_frame(void);
NK_API void                 nk_glfw3_render(enum nk_anti_aliasing, int max_vertex_buffer, int max_element_buffer);

NK_API void                 nk_glfw3_device_destroy(void);
NK_API void                 nk_glfw3_device_create(void);

NK_API void                 nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
NK_API void                 nk_gflw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);
NK_API void                 nk_glfw3_mouse_button_callback(GLFWwindow *win, int button, int action, int mods);

/*
 * ==============================================================
 *
 *                          IMPLEMENTATION
 *
 * ===============================================================
 */
#ifdef NK_GLFW_GL3_IMPLEMENTATION

#ifndef NK_GLFW_TEXT_MAX
#define NK_GLFW_TEXT_MAX 256
#endif
#ifndef NK_GLFW_DOUBLE_CLICK_LO
#define NK_GLFW_DOUBLE_CLICK_LO 0.02
#endif
#ifndef NK_GLFW_DOUBLE_CLICK_HI
#define NK_GLFW_DOUBLE_CLICK_HI 0.2
#endif

struct nk_glfw_device {
    struct nk_buffer cmds;
    struct nk_draw_null_texture null;
    GLuint vbo, vao, ebo;
    GLuint prog;
    GLuint vert_shdr;
    GLuint frag_shdr;
    GLint attrib_pos;
    GLint attrib_uv;
    GLint attrib_col;
    GLint uniform_tex;
    GLint uniform_proj;
    GLuint font_tex;
};

struct nk_glfw_vertex {
    float position[2];
    float uv[2];
    nk_byte col[4];
};

struct nk_glfw {
    GLFWwindow *win;
    int width, height;
    int display_width, display_height;
    struct nk_glfw_device ogl;
    struct nk_context ctx;
    struct nk_font_atlas atlas;
    struct nk_vec2 fb_scale;
    unsigned int text[NK_GLFW_TEXT_MAX];
    int text_len;
    struct nk_vec2 scroll;
    double last_button_click;
    int is_double_click_down;
    struct nk_vec2 double_click_pos;
};

#ifdef __APPLE__
  #define NK_SHADER_VERSION "#version 150\n"
#else
  #define NK_SHADER_VERSION "#version 300 es\n"
#endif

#endif

#define MENU_NONE (1 << 0)
#define MENU_FILE (1 << 1)

#define POPUP_NEW (1 << 2)
#define POPUP_SAVE_AS (1 << 3)
#define POPUP_OPEN (1 << 4)
#define COLOR_MODE_RGBA (1 << 5)
#define COLOR_MODE_HSV (1 << 6)

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
void				nk_example(t_nk *nk);
void				nk_update(t_nk *nk);
void				nk_render(t_nk *nk);
void				nk_position(t_nk *nk, t_vector *vector);
void				nk_combo_vector(t_nk *nk, t_vector *vector, const char *str);
void				nk_combo_colorf(t_nk *nk, t_vector *vec, const char *str);

bool				nk_scene(t_nk *nk, t_scene **scene);
void				nk_cam(t_nk *nk, t_cam *cam);
void 				nk_m_model(t_nk *nk, t_scene *scene, t_m_model *m_model);
void 				nk_model(t_nk *nk, t_scene *scene, t_model *model);
void 				nk_material(t_nk *nk, t_material *material);
void 				nk_m_shader(t_nk *nk, t_m_shader *m_shader);
void 				nk_m_material(t_nk *nk, t_m_material *m_material);
void 				nk_m_light(t_nk *nk, t_scene *scene, t_m_light *m_light);


#endif
