# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2025/11/17 17:47:36 by vramacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

CC 			= 	cc
CFLAGS		= 	-Wall -Wextra -Werror -IIncludes -Ilibft -IMLX42/include

NAME		= 	my_program 
INCD		=	Includes

LIBFT_DIR 	= 	libft
LIBFT 		= 	$(LIBFT_DIR)/libft.a

MLX_DIR		=	MLX42
MLX_BUILD	= 	$(MLX_DIR)/build
MLX_LIB		= 	$(MLX_BUILD)/libmlx42.a

LINKER		= 	-L$(LIBFT_DIR) -lft \
				-L$(MLX_BUILD) -lmlx42 \
				-lglfw -ldl -lm -pthread

SRCFILES	=	main.c \
				utils_error.c \
				window/init_mrt.c \
				window/colors.c 

PARSINGFILES =	parsing.c \
				parsing_utils.c \
				parse_scene.c \
				parse_figures.c \
				parsing_print.c \
				atod.c

GNLFILES	=	get_next_line.c \
				get_next_line_utils.c

SRCS	=	$(addprefix src/,$(SRCFILES)) \
			$(addprefix src/parsing/,$(PARSINGFILES)) \
			$(addprefix get_next_line/,$(GNLFILES))

OBJDIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LINKER) -o $(NAME)
	@echo "$(GREEN)[miniRT]: $(NAME) compiled successfully!$(NC)"

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); \
	fi
	@mkdir -p $(MLX_BUILD)
	@cd $(MLX_BUILD) && cmake .. && make -j4
	@echo "MLX42 built successfully!"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCD) -I$(LIBFT_DIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	
clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)
	@echo "$(RED)[miniRT]: objects cleaned successfully!$(NC)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)
	@echo "$(RED)[miniRT]: $(NAME) cleaned successfully!$(NC)"

re: fclean all

build_mlx: 
	git clone git@github.com:codam-coding-college/MLX42.git MLX42

clean_mlx: 
	rm -rf MLX42

.PHONY: all clean fclean re build_mlx clean_mlx
