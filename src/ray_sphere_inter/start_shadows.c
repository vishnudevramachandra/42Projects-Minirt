/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shadows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:59:40 by majkijew          #+#    #+#             */
/*   Updated: 2025/12/03 13:16:18 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void normal_at(t_obj x, t_tup)
							// various points on a sphere
void	normal_at(t_tup normal, t_tup sp_pos, t_tup point)
{
	sub_tuples(normal, point, sp_pos);
	normalize(normal);
}

void	render_light(t_mrt *m, uint32_t *x, uint32_t *y)
{
	double	px = (2.0 * (*x) / WIDTH - 1.0) * ((double)m->image->width / m->image->height);
	double	py = 1.0 - 2.0 * (*y) / m->image->height;
	t_ray	r;
	t_tup	direction;

	init_vector(direction, px, py, 1);
	create_ray(&r, m->scene->light.position, direction);
}

void	reflect(t_tup out, t_tup in, t_tup normal)
{
	t_tup	normal_comp_ray;

	multi_tuple(normal_comp_ray, normal, 2 * dot_prod(in, normal));
	sub_tuples(out, in, normal_comp_ray);
}

