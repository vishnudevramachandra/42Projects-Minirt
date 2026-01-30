/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:30:49 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/30 22:38:04 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_uv(double *uv, t_tup pt)
{
	uv[0] = acos(pt[1] / magnitude(pt));
	uv[1] = atan2(pt[2], pt[0]);
}

void	scale_u_v(int *u, int *v, double *uv, uint32_t *height_width)
{
	*u = round((uv[0] / M_PI) * (height_width[0] - 1));
	*v = round(((uv[1] / (2 * M_PI)) + 0.5) * (height_width[1] - 1));
}

static void	pattern_at(t_rgb **obj_col, double *uv, t_tup pt, t_inter *i)
{
	int		u;
	int		v;
	uint32_t	height_width[2];

	get_uv(uv, pt);
	height_width[0] = i->obj->tx.mlx_tex->height;
	height_width[1] = i->obj->tx.mlx_tex->width;
	scale_u_v(&u, &v, uv, height_width);
	*obj_col = &i->obj->tx.img[u * height_width[1] + v];
}

void	find_tex_color(t_rgb **obj_col, t_mrt *m, t_inter *i)
{
	t_tup	inv_hit_point;
	t_tup	inv_center_pos;
	t_tup	pt;
	double	uv[2];

	multi_mat_tuple(inv_hit_point, m->inv.final, i->hit_point);
	multi_mat_tuple(inv_center_pos, m->inv.final, i->obj->tx.sub_obj->sp.pos);
	sub_tuples(pt, inv_hit_point, inv_center_pos);
	pattern_at(obj_col, uv, pt, i);
	if (i->obj->tx.typ == BUMP)
		bump_the_normal(i, uv);
}
