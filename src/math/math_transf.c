/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_transf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:15:52 by vramacha          #+#    #+#             */
/*   Updated: 2025/11/19 16:10:33 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minirt.h"

// setup 4D identity matrix
mat4	*identity_mat(mat4 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != j)
				m[i][j] = 0;
			else
				m[i][j] = 1;
			j++;
		}
		i++;
	}
	return ((mat4 *)m);
}

// setup translation matrix using the input parameter
mat4	*translation_mat(mat4 m, double d[3])
{
	int	i;

	i = 0;
	identity_mat(m);
	while (i < 3)
	{
		m[i][3] = d[i];
		i++;
	}
	return ((mat4 *)m);
}

// setup scaling matrix using the input parameter
mat4	*scaling_mat(mat4 m, double d[3])
{
	int	i;

	i = 0;
	identity_mat(m);
	while (i < 3)
	{
		m[i][i] = d[i];
		i++;
	}
	return ((mat4 *)m);
}

// setup rotation matrix using the input parameter
mat4	*rotation_mat(mat4 m, double angles[3])
{
	m[0][0] = cos(angles[0]) * cos(angles[1]);
	m[0][1] = (cos(angles[0]) * sin(angles[1]) * sin(angles[2])) \
		- (sin(angles[0]) * cos(angles[2]));
	m[0][2] = (cos(angles[0]) * sin(angles[1]) * cos(angles[2])) \
		+ (sin(angles[0]) * sin(angles[2]));
	m[0][3] = 0;
	m[1][0] = sin(angles[0]) * cos(angles[1]);
	m[1][1] = (sin(angles[0]) * sin(angles[1]) * sin(angles[2])) \
		+ (cos(angles[0]) * cos(angles[2]));
	m[1][2] = (sin(angles[0]) * sin(angles[1]) * cos(angles[2])) \
		- (cos(angles[0]) * sin(angles[2]));
	m[1][3] = 0;
	m[2][0] = -sin(angles[1]);
	m[2][1] = cos(angles [1]) * sin(angles[2]);
	m[2][2] = cos(angles [1]) * cos(angles[2]);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	return ((mat4 *)m);
}

// setup shearing matrix using the input parameter
mat4	*shearing_mat(mat4 m, double angles[6])
{
	int	i;
	int	j;
	int	k;

	identity_mat(m);
	k = 0;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i != j)
			{
				m[i][j] = angles[k];
				k++;
			}
			j++;
		}
		i++;
	}
	return ((mat4 *)m);
}
