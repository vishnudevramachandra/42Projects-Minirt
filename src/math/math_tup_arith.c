/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tup_arith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:33:35 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/27 17:13:58 by majkijew         ###   ########.fr       */
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

	if (val == 0)
		return ;
	i = 0;
	while (i < 4)
	{
		res[i] = a[i] / val;
		i++;
	}
}
