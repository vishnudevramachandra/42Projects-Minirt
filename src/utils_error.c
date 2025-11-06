/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:27:32 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/06 15:56:34 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"

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

int	is_numeric(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	len_spaces(char *str)
{
	int	len;

	len = 0;
	while (*str == ' ' || *str == '\t')
	{
		str++;
		len++;
	}
	return (len);
}
