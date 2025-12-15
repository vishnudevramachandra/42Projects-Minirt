/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:36 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/15 13:10:19 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	print_color(t_rgb *c)
{
	if (!c)
		return ;

	printf("Color: R=%.2d, G=%.2d, B=%.2d\n", c->r, c->g, c->b);
}

void	color_range(t_rgb *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
}

void	find_obj_color(t_rgb **obj_col, t_inter *i)
{
	if (i->obj->typ == SPHERE)
		*obj_col = &i->obj->sp.color;
	else if (i->obj->typ == PLANE)
		*obj_col = &i->obj->pl.color;
	else
		*obj_col = &i->obj->cy.color;
}

// // uzglednij ambiento color padanie swiatla iwgl
void	final_obj_light(t_rgb *final_col, t_mrt *m, t_inter *i)
{
	t_rgb	ambient;
	t_rgb	*obj_col;

	find_obj_color(&obj_col, i);
	mult_scalar_colors(&ambient, &m->scene->amb_light.color,
		m->scene->amb_light.ratio);
	multi_colors(final_col, obj_col, &ambient);
	t_tup	light_dir;
	sub_tuples(light_dir, m->scene->light.position, i->hit_point);
	normalize(light_dir);
	double	cos_theta;
	cos_theta = dot_prod(i->normal, light_dir);
	// include_shadows();
	if (cos_theta < 0)
		cos_theta = 0;
	// cos_theta = 0.1 + (1 - 0.1) * cos_theta;
	t_rgb diffuse_color;
	mult_scalar_colors(&diffuse_color, &m->scene->light.color,
		cos_theta * m->scene->light.bright_ratio);
	multi_colors(&diffuse_color, obj_col, &diffuse_color);
	add_colors(final_col, final_col, &diffuse_color);
	t_tup view_dir;
	sub_tuples(view_dir, m->scene->camera.position, i->hit_point);
	normalize(view_dir);
 	t_tup reflect_dir;
	t_tup neg_light;
	multi_tuple(neg_light, light_dir, -1);
	reflect(reflect_dir, neg_light, i->normal);
	double spec_angle = dot_prod(reflect_dir, view_dir);
	if(spec_angle < 0) 
		spec_angle = 0;
	double shininess = 100;
	double spec_intensity = pow(spec_angle, shininess);
	// add_to_color(final_col, final_col, ((double)255 * spec_intensity));
	t_rgb spec_color;
	mult_scalar_colors(&spec_color, &m->scene->light.color,
		spec_intensity * m->scene->light.bright_ratio);
	add_colors(final_col, final_col, &spec_color);
	color_range(final_col);
}

void	render_obj(t_mrt *m, t_inter *i, int x, int y)
{
	t_tup	scaled;
	// t_tup	light_dir;
	// t_tup	reflected_dir;
	// double	cos_theta;
	t_rgb final_color;
	
	multi_tuple(scaled, m->ray.direction, i->t);
	add_tuples(i->hit_point, m->ray.origin, scaled);
	normal_at(i->normal, i->obj, i->hit_point);
	// normalize(i->normal);
	// sub_tuples(light_dir, m->scene->light.position, i->hit_point);
	// normalize(light_dir);
	// reflect(reflected_dir, m->ray.direction, i->normal);
	// t_ray ref_ray;
	// create_ray(&ref_ray, i->hit_point, reflected_dir);
	// cos_theta = dot_prod(i->normal, light_dir);
	// if (cos_theta < 0)
	// 	cos_theta = 0;
	// cos_theta = 0.1 + (1 - 0.1) * cos_theta;
	// final_color = mult_scalar_colors(&i->obj->sp.color, cos_theta);
	// mlx_put_pixel(m->image, x, y, get_rgba(&final_color, m->scene->light.bright_ratio));
	final_obj_light(&final_color, m, i);
	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, 1));
}


// void	render_obj(t_mrt *m, t_inter *i, int x, int y)
// {
// 	t_tup	scaled;
// 	t_tup	light_dir;
// 	// t_tup	reflected_dir;
// 	// double	cos_theta;
	

// 	multi_tuple(scaled, m->ray.direction, i->t);
// 	add_tuples(i->hit_point, m->ray.origin, scaled);
// 	normal_at(i->normal, i->obj->sp.pos, i->hit_point);
// 	normalize(i->normal);
// 	sub_tuples(light_dir, m->scene->light.position, i->hit_point);
// 	normalize(light_dir);
// 	// reflect(reflected_dir, m->ray.direction, i->normal);
// 	// t_ray ref_ray;
// 	// create_ray(&ref_ray, i->hit_point, reflected_dir);
// 	final_obj_light();
// 	cos_theta = dot_prod(i->normal, light_dir);
// 	if (cos_theta < 0)
// 		cos_theta = 0;
// 	cos_theta = 0.1 + (1 - 0.1) * cos_theta;
// 	t_rgb final_color = mult_scalar_colors(&i->obj->sp.color, cos_theta);
// 	mlx_put_pixel(m->image, x, y, get_rgba(&final_color, m->scene->light.bright_ratio));
// }

void	insert_intersection(t_inter **list, t_inter *new)
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
}

// those vectors that are supposed to be normal vectors are normalized
void	normalize_vectors(t_mrt *m)
{
	t_list	*cur;
	t_obj	*obj;
	t_tup	vec;

	normalize(m->scene->camera.orientation_vector);
	if (!m->obj)
		return ;
	cur = m->obj;
	while (cur)
	{
		obj = cur->content;
		if (obj->typ == PLANE)
		{
			normalize(obj->pl.norm_vec);
			if (0 < dot_prod(*perpvec_to_plane(vec, &obj->pl), obj->pl.norm_vec))
				multi_tuple(obj->pl.norm_vec, obj->pl.norm_vec, -1);
		}
		cur = cur->next;
	}
}

void	canvas(t_mrt *m)
{
	uint32_t	x;
	uint32_t	y;
	t_view		view;
	t_inter		*i = NULL;

	normalize_vectors(m);
	translate_objects(m);
	project_objects(m);
	setup_viewport(&view, m);
	y = 0;
	while (y < m->image->height)
	{
		x = 0;
		while (x < m->image->width)
		{
			calc_direction(&m->scene->camera, &view, x, y);
			create_ray(&m->ray, m->scene->camera.position,
				m->scene->camera.orientation_vector);
			t_inter	*inter = NULL;
			t_list *current = m->obj;
			while (current)
			{
				t_obj *obj = current->content;
				double t = -1;
				if (obj->typ == SPHERE)
					t = inter_sphere(obj->sp, m->ray);
				else if (obj->typ == PLANE)
					t = inter_plane(&obj->pl, &m->ray);
				// if (obj->typ == CYLINDER)
				// 	t = inter_cylinder(obj->sp, m->ray);
				if (0 < t)
				{	
					i = malloc(sizeof(t_inter));
					i->t = t;
					i->obj = obj;
					i->next = NULL;
					insert_intersection(&inter, i);
				}
				current = current->next;
			}
			if (inter)
			{	
				render_obj(m, inter, x, y);
				free_list(inter);
			}
			x++;
		}
		y++;
	}
}
