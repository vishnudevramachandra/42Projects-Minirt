/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:06:26 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/20 20:26:21 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void print_tup(t_tup vec)
// {
//     printf("     %g,%g,%g", vec[0], vec[1], vec[2]);
// }

double	delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	get_hitpoint( double a, double b, double sqrt_dlt)
{
	double	t;
	double	t1;
	double	t2;

	t1 = ((-b - sqrt_dlt) / (a * 2));
	t2 = ((-b + sqrt_dlt) / (a * 2));

	if (t1 > 0 && t2 > 0)
	{
		if (t1 > t2)
			t = t2;
		else
			t = t1;
	}
	else if (t1 > 0)
		t = t1;
	else if (t2 > 0)
		t = t2;
	else
		t = -1;
	return (t);
}

double	inter_sphere(t_sphere sp, t_ray r)
{
	t_tup	l;
	double	dlt;
	double	t;

	init_vector(l, 0, 0, 0);
	sub_tuples(l, r.origin, sp.pos);
	dlt = delta(dot_prod(r.direction, r.direction),
			2 * dot_prod(r.direction, l), dot_prod(l, l) - sp.dia * sp.dia);
	if (dlt < 0)

		return (-1);
	else if (dlt == 0)
	{
		t = -(2 * dot_prod(r.direction, l))
			/ (dot_prod(r.direction, r.direction)) * 2;
		if (t < 0)
			return (-1);
		return (t);
	}
	else
	{
		t = get_hitpoint(dot_prod(r.direction, r.direction),
				2 * dot_prod(r.direction, l), sqrt(dlt));
	}
	return (t);
}

// int main()
// {
// 	t_sphere	sp;
// 	t_ray		r;
// 	double		t;

// 	sp.dia = 1;
// 	init_point(sp.pos, 1, 0, 5);
// 	// create_ray
// 	init_point(r.origin, 0, 0, 0);
// 	init_vector(r.direction, 1, 0, 5);
// 	printf("before: %f\n", t);
// 	printf("sp pos: ");
// 	print_tup(sp.pos);
// 	printf("\n r.origin: ");
// 	print_tup(r.origin);
// 	printf("\n r.direction: ");
// 	print_tup(r.direction);
// 	printf("\n===============================\n");
// 	t = inter_sphere(sp, r);
// 	printf("after: %f\n", t);
// }
