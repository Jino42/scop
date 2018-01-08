# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2018/01/08 22:01:09 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_FILES = includes/scop.h includes/scop_sdl.h

INC = -I includes/ -I libft/includes -I vector/includes/ -I matrix/includes/ -I SDL2-2.0.5/include

SRC_DIR = srcs/

SRC = main.c \
	  end_of_program.c \
	  init.c \
	  scop_loop.c \
	  update/update_fps.c \
	  sdl/sdl_init.c \
	  sdl/sdl_put_pixel.c \
	  sdl/sdl_key.c \
	  sdl/sdl_exit.c \
	  sdl/sdl_update_event.c \
	  sdl/sdl_end.c

OBJ_DIR = objs/

OBJET = $(SRC:.c=.o)

SDL_DIR = SDL2-2.0.5
SDL_LIB = SDL2-2.0.5/build/.libs/libSDL2.a
SDL_FLAG = $(SDL_LIB) -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl

DIR_LFT = libft/
DIR_VEC = vector/
DIR_MATRIX = matrix/

FLAG_LIB = -lft -lvector -lmatrix

DIR_LIB = libs/

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) lib $(addprefix $(OBJ_DIR), $(OBJET))
	@$(CC) $(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) $(FLAG_LIB) $(SDL_FLAG) $(FRAMEWORK) -o $(NAME)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_VEC) && $(MAKE))
	@(cd $(DIR_MATRIX) && $(MAKE))
	@(cp $(DIR_LFT)libft.a $(DIR_LIB))
	@(cp $(DIR_VEC)libvector.a $(DIR_LIB))
	@(cp $(DIR_MATRIX)libmatrix.a $(DIR_LIB))

$(SDL_DIR):
	@$(shell tar xzf .$(SDL_DIR).tar.gz)

$(SDL_LIB): $(SDL_DIR)
	@cd $(SDL_DIR) && ./configure
	@cd $(SDL_DIR) && make

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)$(SRC_DIR)
	@mkdir $(OBJ_DIR)$/sdl
	@mkdir $(OBJ_DIR)$/update

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
