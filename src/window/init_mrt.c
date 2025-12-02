/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:08:17 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/27 18:45:29 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// void print_tup(t_tup vec)
// {
// 	printf("	 %g,%g,%g\n", vec[0], vec[1], vec[2]);
// }


// void	blend(t_rgb new_color,t_rgb color1, t_rgb color2)
// {
	
// }

// void	render_sphere(t_mrt	*m, uint32_t *x, uint32_t *y)
// {
// 	double px = (2.0 * (*x) / WIDTH - 1.0) * ((double)m->image->width / m->image->height);
// 	double py = 1.0 - 2.0 * (*y) / m->image->height;
	
// 	if (t > 0)
// 		mlx_put_pixel(m->image, *x, *y, rgb(255, 0, 0, 255));
// }

// void	canvas(void *param)
// {
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_mrt		*m;

// 	m = (t_mrt *)param;
// 	while (x < m->image->width)
// 	{
// 		y = 0;
// 		while (y < m->image->height)
// 		{
// 			if (m->obj->typ == SPHERE)
// 				render_sphere(m, &x, &y);
// 			init_light();
// 			y++;
// 		}
// 		x++;
// 	}
// }
// void	ft_somefunc(void *param)

// void	canvas(void *param)
// {
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_mrt		*m;

// 	m = (t_mrt *)param;
// 	x = 0;
// 	while (x < m->image->width)
// 	{
// 		y = 0;
// 		while (y < m->image->height)
// 		{
// 			double py = 1.0 - 2.0 * y / m->image->height;

// 			// normalize(normal);
// 			// normal_at(normal, obj->sp.pos, hit);
// 			// t_tup light_dir;
// 			// sub_tuples(light_dir, light, hit);
// 			// normalize(light_dir);
// 			// normal_at(light_dir, hit, light);
// 			// double cos_theta = dot_prod(normal, light_dir);
// 			// if (co
// 			// if (t > 0)
// 			// {	
// 			// 	// uint32_t base = rgb(255, 0, 0, 255);
// 			// 	// uint32_t shade = rgb(100, 0, 0, 255);
// 			// 	// double a = cos_theta; // użyj cos(theta) jako intensywności światła
// 			// 	// uint32_t final = blend(base, shade, a);
// 			// 	// mlx_put_pixel(m->image, x, y, final);
// 			// 	mlx_put_pixel(m->image, x, y, rgb(0, 0, 0, 255));
// 			// 	if (cos_theta > 0)
// 			// 		mlx_put_pixel(m->image, x, y, rgb(255, 0, 0, 255));
// 			// 	else
// 			// 		mlx_put_pixel(m->image, x, y, rgb(100, 0, 0, 200));
// 			// }
// 			if (t > 0)
// 			{
// 				// uint32_t base  = rgb(100, 0, 0, 255);
// 				// uint32_t shade = rgb(255, 0, 0, 255);
// 				// double a = cos_theta;
// 				// if (a < 0)
// 				// 	a = 0;
// 				// if (a > 1)
// 				// 	a = 1;
// 				// uint32_t final = blend(base, shade, a);
// 				mlx_put_pixel(m->image, x, y, rgb(255, 0, 0, 255));
// 				// render_light(m, &x, &y);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}

// }

// void	render(void *param)
// {
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_mrt		*m;

// 	m = (t_mrt *)param;
// 	x = 0;
// 	t_obj *obj = m->obj->content;
// 	if (obj->typ != SPHERE)
// 		return ;
// 	while (x < m->image->width)
// 	{
// 		y = 0;
// 		while (y < m->image->height)
// 		{
// 			double px = (2.0 * x / WIDTH - 1.0) * ((double)m->image->width / m->image->height);
// 			double py = 1.0 - 2.0 * y / m->image->height;

// 			t_tup	origin;
// 			// t_tup	*light;
// 			t_tup	direction;
// 			init_point(origin, 0, 0, 0); //camera
// 			// light = &m->scene->light.position;
// 			// init_point(light, -40, 20, 15);
// 			init_vector(direction, px, py, 1);
// 			normalize(direction);
// 			t_ray	ray;
// 			create_ray(&ray, origin, direction);
// 			// m->ray = &ray;
// 			double t = inter_sphere(obj->sp, ray);
// 			t_tup hit;
// 			t_tup normal;
// 			// create_ray(&r, m->scene->light.position, direction);

// 			multi_tuple(hit, direction, t);
// 			add_tuples(hit, origin, hit);
// 			sub_tuples(normal, hit, obj->sp.pos);
// 			normalize(normal);
// 			normal_at(normal, obj->sp.pos, hit);
// 			t_tup light_dir;
// 			// sub_tuples(light_dir, light, hit);
// 			normalize(light_dir);
// 			// normal_at(light_dir, hit, light);
// 			double cos_theta = dot_prod(normal, light_dir);
// 			// if (co
// 			// if (t > 0)
// 			// {	
// 			// 	// uint32_t base = rgb(255, 0, 0, 255);
// 			// 	// uint32_t shade = rgb(100, 0, 0, 255);
// 			// 	// double a = cos_theta; // użyj cos(theta) jako intensywności światła
// 			// 	// uint32_t final = blend(base, shade, a);
// 			// 	// mlx_put_pixel(m->image, x, y, final);
// 			// 	mlx_put_pixel(m->image, x, y, rgb(0, 0, 0, 255));
	
// 				// else
// 				// 	mlx_put_pixel(m->image, x, y, rgb(100, 0, 0, 200));
// 			// }
// 			if (t > 0)
// 			{
// 				// uint32_t base  = rgb(100, 0, 0, 255);
// 				// uint32_t shade = rgb(255, 0, 0, 255);
// 				// double a = cos_theta;
// 				// if (a < 0)
// 				// 	a = 0;
// 				// if (a > 1)
// 				// 	a = 1;
// 				// uint32_t final = blend(base, shade, a);
// 				mlx_put_pixel(m->image, x, y, rgb(255, 0, 0, 255));
// 				if (cos_theta > 0)
// 					mlx_put_pixel(m->image, x, y, rgb(225, 225, 225, 225));
// 				// render_light(m, &x, &y);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }

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
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
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
	// render(m);
	canvas(m);
	// render_light(m);
	mlx_loop_hook(m->mlx, ft_hook, m);
	// mlx_loop_hook(m->mlx, canvas, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
}
