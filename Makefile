# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2025/10/31 14:50:53 by majkijew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKER = (idk the linker for math)
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(LINKER) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

build: git@github.com:codam-coding-college/MLX42.git

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

PHONY: all clean fclean re