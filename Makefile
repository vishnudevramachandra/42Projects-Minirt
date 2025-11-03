# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2025/11/03 20:21:48 by majkijew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

CC 			= 	cc
CFLAGS		= 	-Wall -Wextra -Werror
NAME		= 	my_program 
INCD		=	Includes
LIBFT_DIR 	= 	libft
LIBFT 		= 	$(LIBFT_DIR)/libft.a
LINKER		= 	-lft -lm

SRCFILES	= 	utils_error.c \
				parsing.c \
				main.c
GNLFILES	=	get_next_line.c \
				get_next_line_utils.c

SRCS	=	$(addprefix src/,$(SRCFILES)) \
			$(addprefix get_next_line/,$(GNLFILES))

OBJS 	= 	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LINKER) -o $(NAME)
	@echo "$(GREEN)[miniRT]: $(NAME) compiled successfully!$(NC)"

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)
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
