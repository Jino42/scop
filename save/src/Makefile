# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2018/09/19 22:14:15 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nuklear.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

INC_FILES = nuklear.h nuklear_internal.h nuklear_glfw_gl3.h glfw-3.2.1/include/GLFW/glfw3.h

INC = .

OBJ_DIR = objs/

SRC = nuklear_buffer.c \
		nuklear_button.c \
		nuklear_chart.c \
		nuklear_color_picker.c \
		nuklear_color.c \
		nuklear_combo.c \
		nuklear_context.c \
		nuklear_contextual.c \
		nuklear_draw.c \
		nuklear_edit.c \
		nuklear_glfw_gl3.c \
		nuklear_font.c \
		nuklear_group.c \
		nuklear_image.c \
		nuklear_input.c \
		nuklear_layout.c \
		nuklear_list_view.c \
		nuklear_math.c \
		nuklear_menu.c \
		nuklear_page_element.c \
		nuklear_panel.c \
		nuklear_pool.c \
		nuklear_popup.c \
		nuklear_progress.c \
		nuklear_property.c \
		nuklear_scrollbar.c \
		nuklear_selectable.c \
		nuklear_slider.c \
		nuklear_string.c \
		nuklear_style.c \
		nuklear_table.c \
		nuklear_text_editor.c \
		nuklear_text.c \
		nuklear_toggle.c \
		nuklear_tooltip.c \
		nuklear_tree.c \
		nuklear_utf8.c \
		nuklear_util.c \
		nuklear_vertex.c \
		nuklear_widget.c \
		nuklear_window.c \



OBJET = $(SRC:.c=.o)

#.PHONY de $(NAME) = Pas de message, car Verification
.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJET))
	@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OBJET)) && ranlib $(NAME)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -I ./$(INC)  -I glfw-3.2.1/include/GLFW -DNK_GLFW_GL3_IMPLEMENTATION -DNK_INCLUDE_VERTEX_BUFFER_OUTPUT -DNK_INCLUDE_FONT_BAKING -DNK_INCLUDE_DEFAULT_FONT -DNK_IMPLEMENTATION -DNK_GLFW_GL3_IMPLEMENTATION -DNK_INCLUDE_DEFAULT_ALLOCATOR -DNK_INCLUDE_STANDARD_IO -DNK_INCLUDE_FIXED_TYPES -o $@ -c $<

clean:
	@echo "Clean nuklear"
	@/bin/rm -rf $(OBJ_DIR)

fclean:
	@echo "fClean nuklear"
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f $(NAME)

re: fclean all
