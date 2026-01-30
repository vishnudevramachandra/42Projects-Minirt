/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:03:51 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/30 15:00:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	compute_dp_dv(t_tup dp_dv, double *uv, double radius)
{
	dp_dv[0] = -radius * sin(uv[0]) * sin(uv[1]);
	dp_dv[1] = 0;
	dp_dv[2] = radius * sin(uv[0]) * cos(uv[1]);
	dp_dv[3] = 0;
}

static void	compute_dp_du(t_tup dp_du, double *uv, double radius)
{
	dp_du[0] = radius * cos(uv[0]) * cos(uv[1]);
	dp_du[1] = -radius * sin(uv[0]);
	dp_du[2] = radius * cos(uv[0]) * sin(uv[1]);
	dp_du[3] = 0;
}

static void	compute_df_uv(double *df_uv, double *uv, t_inter *i)
{
	int	u0;
	int	u1;
	int	v0;
	int v1;

	scale_uv(uv);
	u0 = round(uv[0] * (i->obj->tx.mlx_tex_b->height - 1));
	v0 = round(uv[1] * (i->obj->tx.mlx_tex_b->width - 1));
	u1 = (u0 + 1) % i->obj->tx.mlx_tex_b->height;
	v1 = (v0 + 1) % i->obj->tx.mlx_tex_b->width;
	df_uv[0] = (double)(i->obj->tx.bump_img[
		u1 * i->obj->tx.mlx_tex_b->width + v0].r
		- i->obj->tx.img[
			u0 * i->obj->tx.mlx_tex_b->width + v0].r) / 255;
	df_uv[1] = (double)(i->obj->tx.bump_img[
		u0 * i->obj->tx.mlx_tex_b->width + v1].r
		- i->obj->tx.img[
			u0 * i->obj->tx.mlx_tex_b->width + v0].r) / 255;
}
static void	compute_n_tilt(
	t_tup n_tilt, t_inter *i, double *uv, double radius)
{
	t_tup	dp_du;
	t_tup	dp_dv;
	double	df_uv[2];
	t_tup	l_cross_prod;
	t_tup	r_cross_prod;

	compute_dp_du(dp_du, uv, radius);
	compute_dp_dv(dp_dv, uv, radius);
	compute_df_uv(df_uv, uv, i);
	cross_prod(l_cross_prod, i->normal, dp_dv);
	cross_prod(r_cross_prod, i->normal, dp_du);
	multi_tuple(l_cross_prod, l_cross_prod, df_uv[0]);
	multi_tuple(r_cross_prod, r_cross_prod, df_uv[1]);
	sub_tuples(n_tilt, l_cross_prod, r_cross_prod);
	div_tuple(n_tilt, n_tilt, radius);
}

void	bump_the_normal(t_inter *i, double *uv)
{
	t_tup	n_tilt;

	compute_n_tilt(n_tilt, i, uv, i->obj->tx.sub_obj->sp.dia / 2);
	add_tuples(i->normal, i->normal, n_tilt);
	normalize(i->normal);
}