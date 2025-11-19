/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_arith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:33:35 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/18 19:25:12 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

void	add_tuples(t_tup res, t_tup a, t_tup b)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] = a[i] + b[i];
		i++;
	}
}

void	sub_tuples(t_tup res, t_tup a, t_tup b)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] = a[i] - b[i];
		i++;
	}
}

void	multi_tuple(t_tup res, t_tup a, double val)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] = a[i] * val;
		i++;
	}
}

void	div_tuple(t_tup res, t_tup a, double val)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] = a[i] / val;
		i++;
	}
}
