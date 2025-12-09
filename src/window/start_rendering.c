/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/09 15:20:12 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;

	multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);

	sub_tuples(i->normal, i->hit_point, i->obj->sp.pos);
	normal_at(i->normal, i->obj->sp.pos, i->hit_point);
	normalize(i->normal);
	t_tup light_dir;
	sub_tuples(light_dir, m->scene->light.position, i->hit_point);
	normalize(light_dir);
	double cos_theta = dot_prod(i->normal, light_dir);
	if (i->t > 0)
	{
		if (cos_theta < 0)
			cos_theta = 0;
		cos_theta = 0.1 + (1 - 0.1) * cos_theta;
		t_rgb final_color = mult_scalar_colors(&i->obj->sp.color, cos_theta);
		mlx_put_pixel(m->image, x, y, get_rgba(&final_color, m->scene->light.bright_ratio));
	}
}

void	calc_intersections(t_inter **list, t_inter *new)
{
	t_inter	*cur;

	if (*list == NULL || new->t < (*list)->t)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next && cur->next->t < new->t)
		cur = cur->next;
	new->next = cur->next;
	cur->next = new;
}

void	free_list(t_inter *i)
{
	t_inter	*temp;

	while (i)
	{
		temp = i->next;
		free(i);
		i = temp;
	}
	normalize(mat[0]);
	cross_prod(mat[1], mat[2], mat[0]);
	node = m->obj;
	while (node)
	{
		obj = node->content;
		if (obj->typ == SPHERE)
			multi_mat_tuple(obj->sp.pos, mat, obj->sp.pos);
		node = node->next;
	}
	multi_mat_tuple(m->scene->light.position, mat, m->scene->light.position);
	copy_vector(m->scene->camera.orientation_vector, (t_tup){0, 0, 1});
}

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_tup		direction;
	t_view		view;
	t_inter		*i = NULL;

	normalize(m->scene->camera.orientation_vector);
	translate_objects(m);
	project_objects(m);
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
			t_inter	*inter = NULL;
			// double	closest_t = INFINITY;
			// t_obj	*closest_obj = NULL;
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
				if (t > 0)
				{	
					i = malloc(sizeof(t_inter));
					i->t = t;
					i->obj = obj;
					i->next = NULL;
					calc_intersections(&inter, i);
				}
				current = current->next;
			}
			if (inter)
			{	
				render_obj(m, inter, x, y);
				free_list(i);
			}
			x++;
		}
		y++;
	}
}
