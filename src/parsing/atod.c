/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:16:17 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/04 13:44:10 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	atofrac(char *str, int *i)
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
double	atod(char *s)
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