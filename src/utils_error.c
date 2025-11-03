/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:27:32 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/01 14:33:49 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Includes/minirt.h"
#include "../libft/libft.h"

void	erro_msg(char *str, int v)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit (v);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

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

// #include <stdio.h>

// int main()
// {
// 	printf("%lf\n", atod("       0.2"));
// 	printf("%lf\n", atod("225.225,225"));
// 	printf("%lf\n", atod("0.0,0.0,20.6"));
// }