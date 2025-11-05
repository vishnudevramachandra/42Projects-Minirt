/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:16:17 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/05 15:47:45 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	atofrac(const char *str, int *i)
{
	double	dev;
	double	result;

	dev = 1.0;
	result = 0.0;
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10.0 + (str[*i] - '0');
		dev *= 10.0;
		(*i)++;
	}
	return (result / dev);
}

//asci to double
double	atod(const char *s)
{
	int		i;
	double	ret;
	double	sign;

	sign = 1.0;
	ret = 0.0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1.0;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = ret * 10 + (s[i] - '0');
		i++;
	}
	ret += atofrac(s, &i);
	return (ret * sign);
}