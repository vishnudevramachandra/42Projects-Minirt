/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:13:17 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/16 14:16:50 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "minirt.h"
# include "../MLX42/include/MLX42/MLX42.h"

// ================================= mlx ===================================
# define HEIGHT 800
# define WIDTH 800

typedef struct s_mlx {
	mlx_t*			mlx;
	mlx_image_t*	image;
	// void			*mlx_ptr;
	// void			*win_ptr;
}	t_mlx;

void	init_mlx(t_mlx *m);

//scene struct

#endif