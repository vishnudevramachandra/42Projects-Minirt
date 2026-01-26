/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:21:52 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/26 14:53:51 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	delta(double a, double b_h, double c)
{
	return ((b_h * b_h) - (a * c));
}

void	get_hitpoint(double *t, double a, double b_h, double sqrt_dlt)
{
	t[0] = (-b_h - sqrt_dlt) / a;
	t[1] = (-b_h + sqrt_dlt) / a;
}
