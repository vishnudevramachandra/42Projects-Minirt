/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:08:17 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 19:48:03 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_hook(void *param)
{
	t_mrt	*m;

	m = (t_mrt *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(m->mlx);
		erro_clean(m, "", 0);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_UP))
		m->image->instances[0].y -= 5;
	if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN))
		m->image->instances[0].y += 5;
	if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
		m->image->instances[0].x += 5;
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
		m->image->instances[0].x -= 5;
}

void	init_mrt(t_mrt *m)
{
	m->mlx = mlx_init(WIDTH, HEIGHT, "minirt", true);
	if (!m->mlx)
		erro_clean(m, "Error", 2);
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	if (!m->image)
	{
		mlx_close_window(m->mlx);
		erro_clean(m, "Error", 2);
	}
	if (mlx_image_to_window(m->mlx, m->image, 0, 0) == -1)
	{
		mlx_close_window(m->mlx);
		erro_clean(m, "Error", 2);
	}
	canvas(m);
	mlx_loop_hook(m->mlx, ft_hook, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
}
