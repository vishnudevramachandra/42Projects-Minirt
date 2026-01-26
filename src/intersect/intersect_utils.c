/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:21:52 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 15:10:51 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	delta(double a, double b_h, double c)
{
	return ((b_h * b_h) - (a * c));
}

void	get_hitpoints(double *t, double a, double b_h, double sqrt_dlt)
{
	double	tmp;

	t[0] = (-b_h - sqrt_dlt) / a;
	t[1] = (-b_h + sqrt_dlt) / a;
	if (t[1] < t[0])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
}
