/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_prod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:01:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/18 18:32:30 by vramacha         ###   ########.fr       */
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
	while (i++ < 4)
		res += a[i] * b[i];
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

void	normalize(t_tup res, t_tup a)
{
	div_tuple(res, a, magnitude(a));
}

// trick function to be implemented most of them need testing but idk