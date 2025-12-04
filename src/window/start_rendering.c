/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/04 11:40:58 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	init_light()
// {
	
// }

// a function that would calculate the direction accordingly to the 
// input but i dont really get it for now
// create_ray(&r, m->scene->camera.position,
// 	direction); x)
void	render_sphere(t_mrt *m, int x, int y)
{
	t_obj	*obj = m->obj->content;
	double	t;

	t = inter_sphere(obj->sp, m->ray);
	if (t > 0)
		mlx_put_pixel(m->image, x, y, get_rgba(&obj->sp.color, 255));
}

// thiss is not entirelly right we have to include the 2 and 3 argument 
// void	calc_direction(t_tup direction, uint32_t x, uint32_t y, t_mrt *m)
// {
// 	double	px;
// 	double	py;

// 	px = (2.0 * (x) / m->image->width - 1.0)
// 		* ((double)m->image->width / m->image->height);
// 	py = 1.0 - 2.0 * (y) / m->image->height;
// 	init_vector(direction, px, py, 1);
// 	normalize(direction);
// }

// camera orientation vector is rotated step-by-step to cover the field of view
void	calc_direction(t_tup dir, t_tup ori_vec, double pitch, double roll)
{
	mat4	m;

	// Create rotation matrix
	rotation_mat(m, (double [3]){0, pitch, roll});
	// Apply combined rotation to the original orientation vector
	multi_mat_tuple(dir, m, ori_vec);
}

// sets up the viewport parameters based on camera and image properties
void	setup_viewport(t_view *view, t_mrt *m)
{
	double	h_field_in_radians;
	double	v_field_in_radians;

	h_field_in_radians = m->scene->camera.horizontal_field / 180 * M_PI;
	view->pitch_start = h_field_in_radians / 2;
	view->pitch_delta= h_field_in_radians / (m->image->width - 1);
	v_field_in_radians = (double)m->image->height / m->image->width\
					* h_field_in_radians;
	view->roll_start = v_field_in_radians / 2;
	view->roll_delta= v_field_in_radians / (m->image->height - 1);
}

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_tup		direction;
	t_obj		*obj;
	t_view		view;

	obj = m->obj->content;
	normalize(m->scene->camera.orientation_vector);
	setup_viewport(&view, m);
	y = 0;
	while (y < m->image->height)
	{
		x = 0;
		while (x < m->image->width)
		{
			calc_direction(direction,
				m->scene->camera.orientation_vector,
				(x * view.pitch_delta) - view.pitch_start,
				(y * view.roll_delta) - view.roll_start);
			// calc_direction(direction, x, y, m);
			create_ray(&m->ray, m->scene->camera.position, direction);
			// m->ray = r;
			if (obj->typ == SPHERE)
				render_sphere(m, x, y);
			// if (obj->typ == PLANE)
			// 	render_plane(m, x, y);
			// if (obj->typ == CYLINDER)
			// 	render_cylinder(m, x, y);
			// init_light();
			x++;
		}
		y++;
	}
}
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