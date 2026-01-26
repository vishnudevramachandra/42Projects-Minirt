/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:21:52 by vramacha          #+#    #+#             */
/*   Updated: 2026/01/25 18:22:26 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	delta(double a, double b_h, double c)
{
	return ((b_h * b_h) - (a * c));
}

double	get_hitpoint(double a, double b_h, double sqrt_dlt)
{
	double	t;
	double	t1;
	double	t2;

	t1 = (-b_h - sqrt_dlt) / a;
	t2 = (-b_h + sqrt_dlt) / a;
	if (0 < t1 || 0 < t2)
	{
		if (t2 < t1)
			t = t2;
		else
			t = t1;
	}
	else
		t = -1;
	return (t);
}
