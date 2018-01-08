# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/12/10 20:45:56 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvector.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

INC_FILES = includes/vector.h

INC = includes/

OBJ_DIR = objs/

SRC = srcs/vector_magnitude.c \
srcs/vector_sqrt_magnitude.c \
srcs/vector_distance.c \
srcs/vector_aequals.c \
srcs/vector_normalize.c \
srcs/vector_add.c \
srcs/vector_sub.c \
srcs/vector_mult.c \
srcs/vector_div.c \
srcs/vector_scale.c \
srcs/vector_clear.c \
srcs/vector_abs.c \
srcs/vector_construct.c \
srcs/vector_copy.c \
srcs/vector_invert.c \
srcs/vector_is_zero.c \
srcs/vector_lerp.c \
srcs/vector_dot.c \
srcs/vector_cross_product.c \
srcs/vector_rotate_x.c \
srcs/vector_rotate_y.c \
srcs/vector_rotate_z.c \
srcs/vector_limit.c \
srcs/vector_floor.c \
srcs/vector_rotate.c

OBJET = $(SRC:.c=.o)

#.PHONY de $(NAME) = Pas de message, car Verification
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
	@echo "Clean libvetor"
	@/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "fClean libvector"
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
