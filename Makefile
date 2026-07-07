# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asato <asato@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/06 15:06:45 by chagen            #+#    #+#              #
#    Updated: 2026/07/02 18:16:50 by chagen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=leak
SRC_DIR		=	src
OBJ_DIR		=	obj
INC_DIR		=	includes
LIBFT_DIR	=	libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a
# Linker directives lmlx is the lmx library on the school computer
LDLIBS		=	$(LIBFT_A) -lmlx -lX11 -lXext -lm

INC			=	-I$(INC_DIR) -I$(LIBFT_DIR)
SRC			=	main.c \
				1_parsing/1_load_map_and_config.c \
				1_parsing/2_parse_file.c \
				1_parsing/3_validate_elements.c \
				1_parsing/4_extract_elements.c \
				1_parsing/5_extract_map.c \
				1_parsing/6_validate_map.c \
				1_parsing/7_validate_start_pos.c \
				1_parsing/8_check_walls.c \
				1_parsing/get_next_line.c \
				2_exec/1_exec.c \
				2_exec/2_init_mlx.c \
				2_exec/3_init_play.c \
				2_exec/4_start_graphics.c \
				2_exec/5_move.c \
				2_exec/utils.c \
				3_raycast/1_raycast.c \
				3_raycast/2_start_values.c \
				3_raycast/3_draw.c \
				3_raycast/4_put_pixel.c \
				3_raycast/5_put_wall.c \
				3_raycast/6_minimap.c \
				3_raycast/7_minimap_utils.c \
				4_cleanup/cleanup.c \
				4_cleanup/error.c \
				4_cleanup/mlx_cleanup.c \

SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC))

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ))

#suppress the "Entering directory" and "Leaving directory" messages
MAKEFLAGS += --no-print-directory

all:	$(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

#compile .o and create their dir if they don't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re
