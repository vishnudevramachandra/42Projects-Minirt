/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:16:55 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 22:11:50 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

void	hadamard_prod(t_tup res, t_tup a, t_tup b)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		res[i] = a[i] * b[i];
		i++;
	}
}

t_rgb	*stripped_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point)
{
	if ((int)floor(dot_prod(param, hit_point)) % 2)
		return (c2);
	else
		return (c1);
}

t_rgb	*ring_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point)
{
	t_tup	res;

	hadamard_prod(res, param, hit_point);
	if ((int)sqrt(dot_prod(res, res)) % 2)
		return (c2);
	else
		return (c1);
}

t_rgb	*checker_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point)
{
	t_tup	res;

	hadamard_prod(res, param, hit_point);
	if ((int)(floor(res[0]) + floor(res[1]) + floor(res[2])) % 2)
		return (c2);
	else
		return (c1);
}

void	find_obj_color(t_rgb **obj_col, t_mrt *m, t_inter *i)
{
	t_tup	inv_hit_point;

	if (!i->obj->sp.mt.pattern.fcn)
		*obj_col = &i->obj->sp.mt.pattern.color1;
	else
	{
		multi_mat_tuple(inv_hit_point, m->inv.final, i->hit_point);
		*obj_col = i->obj->sp.mt.pattern.fcn(
				i->obj->sp.mt.pattern.param,
				&i->obj->sp.mt.pattern.color1,
				&i->obj->sp.mt.pattern.color2,
				inv_hit_point);
	}
}

// int	main()
// {
// 	t_tup	param = {1,0,0,0};
// 	t_rgb	c1 = {255,0,0};
// 	t_rgb	c2 = {0,255,0};
// 	t_rgb	*res;

// 	res = stripped_pattern(param, &c1, &c2, (t_tup){-1.3,0,0,1});
// 	printf("%d,%d,%d\n", res->r, res->g, res->b);
// 	res = stripped_pattern(param, &c1, &c2, (t_tup){-0.5,0,0,1});
// 	printf("%d,%d,%d\n", res->r, res->g, res->b);
// 	res = stripped_pattern(param, &c1, &c2, (t_tup){0.9,0,0,1});
// 	printf("%d,%d,%d\n", res->r, res->g, res->b);
// 	res = stripped_pattern(param, &c1, &c2, (t_tup){1.2,0,0,1});
// 	printf("%d,%d,%d\n", res->r, res->g, res->b);
// }