/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:30:49 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/30 15:05:02 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_uv(double *uv, t_tup pt)
{
	uv[0] = acos(pt[1] / magnitude(pt));
	uv[1] = atan2(pt[2], pt[0]);
}

void scale_uv(double *uv)
{
	uv[0] = uv[0] / M_PI;
	uv[1] = ((uv[1] / (2 * M_PI)) + 0.5);
}

static void	pattern_at(t_rgb **obj_col, double *uv, t_tup pt, t_inter *i)
{
	int		u;
	int		v;

	get_uv(uv, pt);
	scale_uv(uv);
	u = round(uv[0] * (i->obj->tx.mlx_tex->height - 1));
	v = round(uv[1] * (i->obj->tx.mlx_tex->width - 1));
	*obj_col = &i->obj->tx.sub_obj->sp.mt.pattern.color1;
	// *obj_col = &i->obj->tx.img[u * i->obj->tx.mlx_tex->width + v];
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
