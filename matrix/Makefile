# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2018/01/15 20:39:37 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmatrix.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_FILES = includes/matrix.h

INC = includes/

OBJ_DIR = objs/

SRC = srcs/matrix_identity.c \
srcs/matrix_mult_dir_vector.c \
srcs/matrix_mult_matrix.c \
srcs/matrix_mult_vector.c \
srcs/matrix_transpose.c \
srcs/matrix_rotation_x.c \
srcs/matrix_rotation_y.c \
srcs/matrix_rotation_z.c \
srcs/matrix_translation.c

OBJET = $(SRC:.c=.o)

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJET))
	@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJET)) && ranlib $(NAME)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)srcs

$(OBJ_DIR)%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -I ./$(INC) -o $@ -c $<

clean:
	@echo "Clean libmatrix"
	@/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "fClean libmatrix"
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
