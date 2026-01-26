/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vec_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:22:51 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/26 21:05:16 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_vector(t_tup vec, double x, double y, double z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = 0;
}

void	init_point(t_tup vec, double x, double y, double z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = 1;
}

void	copy_tup(t_tup new, t_tup old)
{
	int	i;

	if (new == old)
		return ;
	i = 0;
	while (i < 4)
	{
		new[i] = old[i];
		i++;
	}
}

void	copy_vector(t_tup new, t_tup old)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		new[i] = old[i];
		i++;
	}
	old[i] = 0;
}

void	copy_point(t_tup new, t_tup old)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		new[i] = old[i];
		i++;
	}
	old[i] = 1;
}
