/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_arith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:33:35 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/18 15:00:52 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

t_tup	add_tuples(t_tup *a, t_tup *b)
{
	return ((t_tup){a->x + b->x,
		a->y + b->y,
		a->z + b->z,
		a->w + b->w});
}

t_tup	sub_tuples(t_tup *a, t_tup *b)
{
	return ((t_tup){a->x - b->x,
		a->y - b->y,
		a->z - b->z,
		a->w - b->w});
}

t_tup	multi_tuple(t_tup *a, double val)
{
	return ((t_tup){a->x * val,
		a->y * val,
		a->z * val,
		a->w * val});
}

t_tup	div_tuple(t_tup *a, double val)
{
	return ((t_tup){a->x / val,
		a->y / val,
		a->z / val,
		a->w / val});
}
