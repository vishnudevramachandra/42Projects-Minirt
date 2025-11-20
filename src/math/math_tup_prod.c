/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_prod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:01:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/20 22:29:14 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../Includes/minirt.h"

double	dot_prod(t_tup a, t_tup b)
{
	int		i;
	double	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res += a[i] * b[i];
		i++;
	}
	return (res);
}

void	cross_prod(t_tup res, t_tup a, t_tup b)
{
	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

double	magnitude(t_tup a)
{
	return (sqrt(dot_prod(a, a)));
}

// Normalization is the process of taking an arbitrary vector and converting it
// into a unit vector. It will keep your calculations anchored relative to a common
// scale (the unit vector), which is pretty important. If you were to skip normalizing your ray vectors or your surface normals, your calculations would be
// scaled differently for every ray you cast, and your scenes would look terrible
// (if they rendered at all).

void	normalize(t_tup a)
{
	div_tuple(a, a, magnitude(a));
}
// void	normalize(t_tup res, t_tup a)
// {
// 	div_tuple(res, a, magnitude(a));
// }

void	multi_and_accum_tuple(t_tup res, t_tup a, double val)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] += a[i] * val;
		i++;
	}
}
// trick function to be implemented most of them need testing but idk