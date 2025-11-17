/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:08:17 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/17 17:58:57 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	canvas(void *param)
// {
	
// }

void	ft_somefunc(void *param)
{
	uint32_t	i;
	uint32_t	y;
	t_mrt		*m;

	m = (t_mrt *)param;
	i = 0;
	// printf("color? %x\n", get_rgba(&m->a->amb_light.color, m->a->amb_light.ratio));
	while (i < m->image->width)
	{
		y = 0;
		while (y < m->image->height)
		{
			mlx_put_pixel(m->image, i, y, get_rgba(&m->scene->amb_light.color, m->scene->amb_light.ratio));
			y++;
		}
		i++;
	}
}

//idk i think here we will have to adjust the camera position or something 
void	ft_hook(void *param)
{
	t_mrt	*m;

	m = (t_mrt *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(m->mlx);
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
		erro_msg("ERROR", 2);
	m->image = mlx_new_image(m->mlx, 128, 128);
	if (!m->image)
	{
		mlx_close_window(m->mlx);
		erro_msg("ERROR", 2);
	}
	if (mlx_image_to_window(m->mlx, m->image, 0, 0) == -1)
	{
		mlx_close_window(m->mlx);
		erro_msg("ERROR", 2);
	}
	mlx_loop_hook(m->mlx, ft_somefunc, m);
	mlx_loop_hook(m->mlx, ft_hook, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
}
