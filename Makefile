# **************************************************************************** #
#	                                                                          #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/31 14:49:49 by majkijew          #+#    #+#              #
#    Updated: 2026/01/31 01:36:58 by majkijew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN  := \033[0;32m
YELLOW := \033[0;33m
RED    := \033[0;31m
NC     := \033[0m

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Imandatory/Includes -Ilibft -IMLX42/include
CFLAGS_BONUS  = -Wall -Wextra -Werror -Ibonus/Includes -Ilibft -IMLX42/include

NAME    = miniRT
INCD    = Includes

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR   = MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB   = $(MLX_BUILD)/libmlx42.a

LINKER    = -L$(LIBFT_DIR) -lft \
            -L$(MLX_BUILD) -lmlx42 \
            -lglfw -ldl -lm -pthread

OBJDIR = obj

# ==========================
# MANDATORY SOURCE FILES
# ==========================

MANDATORY_SRCFILES = 	main.c \
						window/init_mrt.c \
						window/colors.c \
						window/color_arith.c \
						window/lights.c \
						window/shadows.c \
						window/insert_utils.c \
						window/camera.c \
						rendering/start_rendering.c \
						rendering/normalization.c \
						rendering/translation.c \
						rendering/projection.c \
						ray_inter/create_rays.c \
						ray_inter/start_shadows.c \
						intersect/intersect_sphere.c \
						intersect/intersect_plane.c \
						intersect/intersect_cylinder.c \
						intersect/intersect_utils.c

MANDATORY_PARSINGFILES = 	parsing/parsing.c \
							parsing/utils.c \
							parsing/utils_error.c \
							parsing/scene_validation.c \
							parsing/parsing_utils.c \
							parsing/parsing_utils2.c \
							parsing/parse_scene.c \
							parsing/parse_figures.c \
							parsing/atod.c

MANDATORY_MATHFILES = math/init_vec_pos.c math/math_matrix.c math/math_transf.c \
	math/math_tup_arith.c math/math_tup_prod.c

MANDATORY_GNLFILES  = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

MANDATORY_SRCS = $(addprefix mandatory/src/,$(MANDATORY_SRCFILES)) \
				 $(addprefix mandatory/src/,$(MANDATORY_PARSINGFILES)) \
				 $(addprefix mandatory/src/,$(MANDATORY_MATHFILES)) \
				 $(addprefix ,$(MANDATORY_GNLFILES))

MANDATORY_OBJS = $(MANDATORY_SRCS:%.c=$(OBJDIR)/%.o)

# ==========================
# BONUS SOURCE FILES
# ==========================

BONUS_SRCFILES = main.c \
					window/init_mrt.c \
					window/colors.c \
					window/color_arith.c \
					window/lights.c \
					window/shadows.c \
					window/insert_utils.c \
					window/camera.c \
					window/pattern.c \
					window/texture.c \
					window/texture_helper.c \
					rendering/start_rendering.c \
					rendering/normalization.c \
					rendering/translation.c \
					rendering/projection.c \
					ray_inter/create_rays.c \
					ray_inter/start_shadows.c \
					intersect/intersect_sphere.c \
					intersect/intersect_plane.c \
					intersect/intersect_cylinder.c \
					intersect/intersect_cone.c \
					intersect/intersect_utils.c

BONUS_PARSINGFILES = parsing.c \
						utils.c \
						utils_error.c \
						scene_validation.c \
						parsing_utils.c \
						parsing_utils2.c \
						parse_scene.c \
						parse_figures.c \
						parse_patterns.c \
						parse_texture.c \
						parse_texture_utils.c \
						atod.c

BONUS_MATHFILES = math/init_vec_pos.c math/math_matrix.c math/math_transf.c \
	math/math_tup_arith.c math/math_tup_prod.c

BONUS_GNLFILES  = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

BONUS_SRCS = $(addprefix bonus/src/,$(BONUS_SRCFILES)) \
			 $(addprefix bonus/src/parsing/,$(BONUS_PARSINGFILES)) \
			 $(addprefix bonus/src/,$(BONUS_MATHFILES)) \
			 $(addprefix ,$(BONUS_GNLFILES))

BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJDIR)/%.o)

all: mandatory

mandatory: $(MANDATORY_OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LINKER) -o $(NAME)
	@echo "$(GREEN)[miniRT]: mandatory compiled successfully!$(NC)"

bonus: CFLAGS = $(CFLAGS_BONUS)
bonus:	$(BONUS_OBJS) $(LIBFT) $(MLX_LIB)
		$(CC) $(CFLAGS_BONUS) $(BONUS_OBJS) $(LINKER) -o $(NAME)
		@echo "$(GREEN)[miniRT]: bonus compiled successfully!$(NC)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(MLX_LIB): build_mlx
	@echo "$(GREEN)MLX42 library ready$(NC)"

build_mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); \
	fi
	@mkdir -p $(MLX_BUILD)
	@cd $(MLX_BUILD) && cmake .. && make -j4
	@echo "$(GREEN)MLX42 built successfully!$(NC)"
clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)
	@echo "$(RED)[miniRT]: objects cleaned$(NC)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "$(RED)[miniRT]: binary cleaned$(NC)"

re: fclean all

.PHONY: all mandatory bonus clean fclean re
