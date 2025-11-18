/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_prod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:01:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/18 15:08:54 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../../Includes/minirt.h"

double	dot_prod(t_tup *a, t_tup *b)
{
	return (a->x * b->x
		+ a->y * b->y
		+ a->z * b->z
		+ a->w * b->w);
}

t_tup	cross_prod(t_tup *a, t_tup *b)
{
	return ((t_tup){a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x});
}

double	magnitude(t_tup *a)
{
	return (sqrt(a->x * a->x
			+ a->y * a->y
			+ a->z * a->z));
}

t_tup	normalize(t_tup *a)
{
	return (div_tuple(a, magnitude(a)));
}

// trick function to be implemented most of them need testing but idk