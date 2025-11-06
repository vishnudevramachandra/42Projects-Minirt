# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2025/11/05 22:48:31 by vramacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

CC 			= 	cc
CFLAGS		= 	-Wall -Wextra -Werror -IIncludes -Ilibft
NAME		= 	my_program 
INCD		=	Includes
LIBFT_DIR 	= 	libft
LIBFT 		= 	$(LIBFT_DIR)/libft.a
LINKER		= 	-lft -lm

SRCFILES	=	main.c \
				utils_error.c

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

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LINKER) -o $(NAME)
	@echo "$(GREEN)[miniRT]: $(NAME) compiled successfully!$(NC)"

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@make -C $(LIBFT_DIR)

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
