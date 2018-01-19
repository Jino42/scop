# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/10/18 15:26:38 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

INC_FILES = includes/btree.h includes/libft.h includes/get_next_line.h includes/ft_printf.h

INC = includes/

OBJ_DIR = objs/

SRC = basic/ft_memset.c \
	  basic/ft_bzero.c \
	  basic/ft_memcpy.c \
	  basic/ft_memccpy.c \
	  basic/ft_memmove.c \
	  basic/ft_memchr.c \
	  basic/ft_memcmp.c \
	  basic/ft_strlen.c \
	  basic/ft_strdup.c \
	  basic/ft_strcpy.c \
	  basic/ft_strcat.c \
	  basic/ft_strncat.c \
	  basic/ft_strlcat.c \
	  basic/ft_strchr.c \
	  basic/ft_strrchr.c \
	  basic/ft_strstr.c \
	  basic/ft_strnstr.c \
	  basic/ft_strcmp.c \
	  basic/ft_strncmp.c \
	  basic/ft_atoi.c \
	  basic/ft_isalpha.c \
	  basic/ft_isdigit.c \
	  basic/ft_isalnum.c \
	  basic/ft_isascii.c \
	  basic/ft_isprint.c \
	  basic/ft_toupper.c \
	  basic/ft_tolower.c \
	  basic/ft_memalloc.c \
	  basic/ft_memdel.c \
	  basic/ft_strnew.c \
	  basic/ft_strdel.c \
	  basic/ft_strclr.c \
	  basic/ft_striter.c \
	  basic/ft_striteri.c \
	  basic/ft_strmap.c \
	  basic/ft_strmapi.c \
	  basic/ft_strequ.c \
	  basic/ft_strnequ.c \
	  basic/ft_strsub.c \
	  basic/ft_strjoin.c \
	  basic/ft_strtrim.c \
	  basic/ft_strsplit.c \
	  basic/ft_itoa.c \
	  basic/ft_putchar.c \
	  basic/ft_putstr.c \
	  basic/ft_putendl.c \
	  basic/ft_putnbr.c \
	  basic/ft_putchar_fd.c \
	  basic/ft_putstr_fd.c \
	  basic/ft_putendl_fd.c \
	  basic/ft_putnbr_fd.c \
	  basic/ft_lstnew.c \
	  basic/ft_lstdelone.c \
	  basic/ft_lstdel.c \
	  basic/ft_lstadd.c \
	  basic/ft_lstiter.c \
	  basic/ft_lstmap.c \
	  basic/ft_strncpy.c \
	  basic/ft_atoi_base.c \
	  basic/ft_itoa_base.c \
	  basic/get_next_line.c \
	  basic/ft_abs.c \
	  basic/ft_error.c \
	  basic/ft_realloc.c \
	  basic/ft_lstinsert.c \
	  basic/ft_isin.c \
	  ft_printf/ft_printf.c \
	  ft_printf/check.c \
	  ft_printf/write_other.c \
	  ft_printf/write_width.c \
	  ft_printf/dipfoux.c \
	  ft_printf/sc_c.c \
	  ft_printf/sc_s.c \
	  ft_printf/preci.c \
	  ft_printf/arg_dipfoux.c \
	  ft_printf/write_f.c \
	  ft_printf/printf_loop.c \
	  ft_printf/ft_putbuffer.c \
	  ft_printf/tools_ft_printf/ft_multitoa_base.c \
	  ft_printf/tools_ft_printf/ft_putwchar.c \
	  ft_printf/tools_ft_printf/ft_putwstr.c \
	  ft_printf/tools_ft_printf/ft_sizebit.c \
	  ft_printf/tools_ft_printf/ft_wcharlen.c \
	  ft_printf/tools_ft_printf/ft_putnbrbase.c \
	  ft_printf/tools_ft_printf/ft_wctoc.c \
	  ft_printf/tools_ft_printf/ft_watoa.c \
	  ft_printf/tools_ft_printf/ft_wstrlen.c \
	  ft_printf/tools_ft_printf/ft_wstrnew.c \
	  ft_printf/tools_ft_printf/ft_wstrsub.c \
	  ft_printf/tools_ft_printf/ft_strjoinfree.c \
	  ft_printf/tools_ft_printf/ft_dotoa.c \
	  btree/srcs/btree_create_node.c \
	  btree/srcs/btree_create_leaf.c \
	  btree/srcs/btree_child_left.c \
	  btree/srcs/btree_child_right.c \
	  btree/srcs/btree_is_leaf.c \
	  btree/srcs/btree_is_empty.c \
	  btree/srcs/btree_size.c \
	  btree/srcs/btree_insert_right.c \
	  btree/srcs/btree_insert_left.c \
	  btree/srcs/btree_delete_right.c \
	  btree/srcs/btree_delete_left.c \
	  btree/srcs/btree_depth_insert_right.c \
	  btree/srcs/btree_depth_insert_left.c \
	  btree/srcs/btree_apply_prefix.c \
	  btree/srcs/btree_apply_infix.c \
	  btree/srcs/btree_apply_suffix.c \
	  btree/srcs/btree_apply_free.c \
	  btree/srcs/btree_insert_data.c \
	  btree/srcs/btree_search_item.c \
	  btree/srcs/btree_insert_infix_data.c \
	  btree/srcs/btree_ul_insert_infix_data.c \
	  btree/srcs/btree_finsert_infix_data.c \
	  btree/srcs/btree_env_apply_infix.c \
	  

OBJET = $(SRC:.c=.o)

#.PHONY de $(NAME) = Pas de message, car Verification
.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJET))
	@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJET)) && ranlib $(NAME)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)basic
	mkdir $(OBJ_DIR)btree
	mkdir $(OBJ_DIR)btree/srcs
	mkdir $(OBJ_DIR)ft_printf
	mkdir $(OBJ_DIR)ft_printf/tools_ft_printf

$(OBJ_DIR)%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -I ./$(INC) -o $@ -c $<

clean:
	@echo "Clean libft"
	@/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "fClean libft"
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
