# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2018/01/18 23:40:31 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_FILES = includes/scop.h includes/scop_glfw.h

INC = -I includes/ -I libft/includes -I vector/includes/ -I matrix/includes/ -I glfw-3.2.1/include/GLFW/

SRC_DIR = srcs/

SRC = main.c \
	  end_of_program.c \
	  init.c \
	  glad.c \
	  shader_construct.c \
	  glfw_init.c \
	  tools.c \
	  matrix_view.c \
	  matrix_projection.c \
	  glfw_temp.c \
	  render_loop.c \
	  parsing/parsing_temp.c \
	  update/update_fps.c \
	  event/event_mouse.c \
	  event/event_cam.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

GLFW_DIR = ./glfw-3.2.1/construct
GLFW_LIB = $(GLFW_DIR)/src/libglfw3.a
GLFW_FLAG = $(GLFW_LIB) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl

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
