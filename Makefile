# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2025/10/31 15:07:51 by majkijew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = my_program
# LINKER = -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
# 	$(CC) $(CFLAGS) $(SRC) $(LINKER) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

build: 
	git clone git@github.com:codam-coding-college/MLX42.git MLX42

clean_lib: 
	rm -rf MLX42

.PHONY: all clean fclean re build
