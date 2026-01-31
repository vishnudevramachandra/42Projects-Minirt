/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:33:04 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 15:51:44 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_ambient_component(t_rgb *final_col, t_rgb *obj_col, t_mrt *m)
{
	t_rgb	ambient_illumination;

	mult_scalar_colors(&ambient_illumination, &m->scene->amb_light.color,
		m->scene->amb_light.ratio);
	multi_colors(final_col, obj_col, &ambient_illumination);
}

void	add_direct_component(t_rgb *final_col, t_rgb *obj_col, t_light *light,
	double cos_theta)
{
	t_rgb	direct_illumination;
	t_rgb	direct_color;

	mult_scalar_colors(&direct_illumination, &light->color,
		cos_theta * light->bright_ratio);
	multi_colors(&direct_color, obj_col, &direct_illumination);
	add_colors(final_col, final_col, &direct_color);
}

double	cos_fac(t_mrt *m, t_inter *i, t_tup light_unit_vec)
{
	t_tup	view_unit_vec;
	t_tup	neg_vec;
	t_tup	reflected_light_vec;

	sub_tuples(view_unit_vec, m->scene->camera.position, i->hit_point);
	normalize(view_unit_vec);
	multi_tuple(neg_vec, light_unit_vec, -1);
	reflect(reflected_light_vec, neg_vec, i->normal);
	return (dot_prod(reflected_light_vec, view_unit_vec));
}

void	add_specular_component(
	t_rgb *final_col, t_light *light, double shininess, double cos_theta)
{
	t_rgb	spec_color;

	if (cos_theta <= 0)
		return ;
	mult_scalar_colors(&spec_color,
		&light->color,
		pow(cos_theta, shininess) * light->bright_ratio);
	add_colors(final_col, final_col, &spec_color);
}

void	final_obj_color(t_rgb *final_c, t_mrt *m, t_inter *i)
{
	t_rgb	obj_c;
	t_tup	light_uv;
	t_list	*node;
	t_light	*lt;

	node = m->scene->lights_list;
	find_obj_color(&obj_c, i);
	add_ambient_component(final_c, &obj_c, m);
	while (node)
	{
		lt = node->content;
		if (is_in_shadow(m, i, light_uv, lt)
			|| dot_prod(i->normal, light_uv) <= 0)
		{
			node = node->next;
			continue ;
		}
		add_direct_component(final_c, &obj_c, lt,
			dot_prod(i->normal, light_uv));
		add_specular_component(final_c, lt, (double)150,
			cos_fac(m, i, light_uv));
		node = node->next;
	}
	color_range(final_c);
}
