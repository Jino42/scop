/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 22:00:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 22:07:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
# include "nuklear_glfw_gl3.h"
/*
struct nk_context*   nk_glfw3_init(GLFWwindow *win, enum nk_glfw_init_state);
void                 nk_glfw3_shutdown(void);
void                 nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas);
void                 nk_glfw3_font_stash_end(void);
void                 nk_glfw3_new_frame(void);
void                 nk_glfw3_render(enum nk_anti_aliasing, int max_vertex_buffer, int max_element_buffer);

void                 nk_glfw3_device_destroy(void);
void                 nk_glfw3_device_create(void);

void                 nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
void                 nk_gflw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);
void                 nk_glfw3_mouse_button_callback(GLFWwindow *win, int button, int action, int mods);
*/
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
	glfwPollEvents();
	strcpy(nk->buffer_text, "./json/");
	return (nk);
}

void				*nk_destruct(t_nk **nk)
{
	if (nk && *nk)
	{
		nk_glfw3_shutdown();
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
