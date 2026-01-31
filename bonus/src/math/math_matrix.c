/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:43:04 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/31 15:20:55 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

// matrix-matrix multiplication carried out as combination of rows
t_mat4	*multi_mat_mat(t_mat4 res, t_mat4 a, t_mat4 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 16)
	{
		*((double *)res + i) = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			multi_and_accum_tuple(res[i], b[j], a[i][j]);
			j++;
		}
		i++;
	}
	return ((t_mat4 *)res);
}

// matrix-tuple multiplication carried out using dot-products
t_tup	*multi_mat_tuple(t_tup res, t_mat4 m, t_tup t)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		res[i] = dot_prod(m[i], t);
		i++;
	}
	return ((t_tup *)res);
}

// in-place transpose of matrix
void	transpose_mat(t_mat4 m)
{
	int		i;
	int		j;
	double	tmp;

	i = 0;
	while (i < 4)
	{
		j = i + 1;
		while (j < 4)
		{
			tmp = m[j][i];
			m[j][i] = m[i][j];
			m[i][j] = tmp;
			j++;
		}
		i++;
	}
}

// matrix comparison using epsilon
bool	is_equal_mat(t_mat4 a, t_mat4 b)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!is_equal_tup(a[i], b[i]))
			return (0);
		i++;
	}
	return (1);
}

t_mat4	*copy_mat(t_mat4 new, t_mat4 old)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		*((double *)new + i) = *((double *)old + i);
		i++;
	}
	return ((t_mat4 *)new);
}
