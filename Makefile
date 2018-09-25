# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2018/09/25 20:24:19 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Wvla -g3

INC_FILES = includes/scop.h includes/scop_glfw.h includes/scop_nk.h includes/c_scene.h includes/c_texture.h includes/json.h includes/c_lm.h  includes/c_cam.h includes/c_light.h includes/c_material.h includes/c_mesh.h includes/c_model.h includes/c_shader.h includes/c_rbo.h

INC = -I includes/ -I libft/includes -I vector/includes/ -I matrix/includes/ -I glfw-3.2.1/include/GLFW/ -g3 -I ~/.brew/include/ -I ./cJSON/ -I glad/ -I nuklear/src/

SANIT = -fsanitize=address

SRC_DIR = srcs/

SRC = main.c \
		../glad/glad.c \
		loop.c \
		c_rbo.c \
		flag.c \
		c_env.c \
		c_fps.c \
		c_scene/scene.c \
		c_scene/scene_uniform.c \
		c_scene/scene_uniform_lights.c \
		c_scene/scene_uniform_texture.c \
		c_scene/scene_render.c \
		c_scene/scene_parse.c \
		c_scene/scene_tools.c \
		c_scene/scene_write.c \
		c_scene/scene_require.c \
		c_cam/cam.c \
		c_cam/cam_update.c \
		c_texture/texture.c \
		c_texture/texture_load_tga.c \
		c_texture/m_texture.c \
		c_shader/shader.c \
		c_shader/shader_build.c \
		c_shader/m_shader.c \
		c_shader/m_shader_parse.c \
		c_shader/m_shader_write.c \
		c_shader/m_shader_get_index.c \
		c_mesh/mesh.c \
		c_mesh/m_mesh.c \
		c_mesh/mesh_gen_gl_buffers.c \
		c_mesh/mesh_gen_gl_buffers_spe.c \
		c_model/model.c \
		c_model/m_model_hidden.c \
		c_model/m_model_update.c \
		c_model/model_tools.c \
		c_model/m_model.c \
		c_model/m_model_parse.c \
		c_model/m_model_parse_get_index.c \
		c_model/m_model_write.c \
		c_material/material.c \
		c_material/m_material.c \
		c_material/m_material_write.c \
		c_material/m_material_parse.c \
		c_material/m_material_get_index.c \
		c_light/light.c \
		c_light/light_update.c \
		c_light/m_light.c \
		c_light/m_light_render.c \
		c_light/m_light_write.c \
		c_light/m_light_parse.c \
		json/json_tools.c \
		json/json_parse.c \
		json/json_write.c \
		json/json_error.c \
		load_model/c_lm.c \
		load_model/load_model.c \
		glfw/glfw_construct.c \
		glfw/glfw_destruct.c \
		glfw/glfw_update.c \
		event/event_mouse.c \
		nk/nk.c \
		nk/nk_menu.c \
		nk/nk_style.c \
		nk/nk_widget_color.c \
		nk/nk_widget.c \
		nk/nk_m_material.c \
		nk/nk_material.c \
		nk/nk_light.c \
		nk/nk_m_light.c \
		nk/nk_model.c \
		nk/nk_cam.c \
		nk/nk_scene.c \
		nk/nk_m_model.c \
		tools/matrixgl_view.c \
		tools/radian_degree.c \
		tools/matrixgl_projection.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

GLFW_DIR = ./glfw-3.2.1/construct
GLFW_LIB = $(GLFW_DIR)/src/libglfw3.a
GLFW_FLAG = $(GLFW_LIB) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl -L ~/.brew/lib/ -lGLEW nuklear/src/nuklear.a -L ./cJSON/build/ -lcjson

DIR_LFT = libft/
DIR_VEC = vector/
DIR_MATRIX = matrix/

FLAG_LIB = -lft -lvector -lmatrix

DIR_LIB = libs/

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) $(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) $(FLAG_LIB) $(GLFW_FLAG) $(FRAMEWORK) -o $(NAME)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_VEC) && $(MAKE))
	@(cd $(DIR_MATRIX) && $(MAKE))
	@(cp $(DIR_LFT)libft.a $(DIR_LIB))
	@(cp $(DIR_VEC)libvector.a $(DIR_LIB))
	@(cp $(DIR_MATRIX)libmatrix.a $(DIR_LIB))

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)$(SRC_DIR)
	@mkdir $(OBJ_DIR)$/update
	@mkdir $(OBJ_DIR)$/glfw
	@mkdir $(OBJ_DIR)$/event
	@mkdir $(OBJ_DIR)$/parsing
	@mkdir $(OBJ_DIR)$/tools
	@mkdir $(OBJ_DIR)$/load_model
	@mkdir $(OBJ_DIR)$/nk
	@mkdir $(OBJ_DIR)$/json
	@mkdir $(OBJ_DIR)$/c_mesh
	@mkdir $(OBJ_DIR)$/c_shader
	@mkdir $(OBJ_DIR)$/c_cam
	@mkdir $(OBJ_DIR)$/c_light
	@mkdir $(OBJ_DIR)$/c_model
	@mkdir $(OBJ_DIR)$/c_material
	@mkdir $(OBJ_DIR)$/c_texture
	@mkdir $(OBJ_DIR)$/c_scene

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "build $<"

clean:
	@echo "Clean scop"
	@(cd $(DIR_LFT) && $(MAKE) clean)
	@(cd $(DIR_VEC) && $(MAKE) clean)
	@(cd $(DIR_MATRIX) && $(MAKE) clean)
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -rf $(DIR_LIB)

fclean:
	@echo "fClean scop"
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && $(MAKE) fclean)
	@(cd $(DIR_VEC) && $(MAKE) fclean)
	@(cd $(DIR_MATRIX) && $(MAKE) fclean)
	@/bin/rm -rf $(DIR_LIB)
	@/bin/rm -f $(NAME)

re: fclean all

clean_project:
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)

project: clean_project all
