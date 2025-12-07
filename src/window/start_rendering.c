/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/07 21:05:44 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_obj(t_mrt *m, t_obj *obj, int x, int y)
{
	// t_obj	*obj = m->obj->content;
	double	t;
	t_tup	hit_point;
	t_tup	normal;

	if (obj->typ == SPHERE)
		t = inter_sphere(obj->sp, m->ray);
	else if (obj->typ == PLANE)	
		t = inter_plane(obj->pl, m->ray);
	multi_tuple(hit_point, m->ray.direction, t);
	normal_at(normal, &obj->sp.dia, hit_point);
	t_tup light_dir;
	sub_tuples(light_dir, m->scene->light.position, hit_point);
	normalize(light_dir);
	double cos_theta = dot_prod(normal, light_dir);
	if (t > 0)
	{
		if (cos_theta < 0)
			cos_theta = 0;
		cos_theta = 0.1 + (1 - 0.1) * cos_theta;
		t_rgb final_color = mult_scalar_colors(&obj->sp.color, cos_theta);
		mlx_put_pixel(m->image, x, y, get_rgba(&final_color, m->scene->light.bright_ratio));
	}
}

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

//for every pixel i am looking for the nearest object 
void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_tup		direction;
	t_view		view;

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
			create_ray(&m->ray, m->scene->camera.position, direction);
			double closest_t = INFINITY;
			t_obj *closest_obj = NULL;
			t_list *current = m->obj;
			while (current)
			{
				t_obj *obj = current->content;
				double t = -1;
				if (obj->typ == SPHERE)
					t = inter_sphere(obj->sp, m->ray);
				// if (obj->typ == PLANE)
				// 	t = inter_plane(obj->sp, m->ray);
				// if (obj->typ == CYLINDER)
				// 	t = inter_cylinder(obj->sp, m->ray);
				if (t > 0 && t < closest_t)
				{
					closest_t = t;
					closest_obj = obj;
				}
				current = current->next;
			}
			if (closest_obj)
				render_obj(m, closest_obj, x, y);
			x++;
		}
		y++;
	}
}
