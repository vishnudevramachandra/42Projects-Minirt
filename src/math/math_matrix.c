/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:43:04 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/19 11:18:57 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// matrix-matrix multiplication carried out as combination of rows
void	multi_mat_mat(mat4 res, mat4 a, mat4 b)
{
	int	i;
	int	j;

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
}

// matrix-tuple multiplication carried out using dot-products
void	multi_mat_tuple(t_tup res, mat4 a, t_tup b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		res[i] = dot_prod(a[i], b);
		i++;
	}
}

// in-place transpose of matrix
void	transpose_mat(mat4 m)
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
bool	is_equal_mat(mat4 a, mat4 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (__DBL_EPSILON__ < fabs(a[i][j] - b[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
