/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:19:54 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 15:22:00 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt_bonus.h"

int	get_double_len(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '.')
		return (0);
	if (s[i] == '-')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '.')
	{
		if (!(s[i + 1] >= '0' && s[i + 1] <= '9'))
			return (0);
		i++;
		while (s[i] >= '0' && s[i] <= '9')
			i++;
	}
	if (i == 0 || (i == 1 && s[0] == '-'))
		return (0);
	return (i);
}

int	set_double(double *d, const char *s, int *len)
{
	*len = get_double_len(s);
	if (len <= 0)
		return (0);
	*d = atod(s);
	return (*len);
}

int	set_tuple(t_tup v, const char *s, int *len, double w)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3 && s[i] && s[i] != '\n')
	{
		set_double(&v[j], s + i, len);
		if (!*len || (j < 2 && s[i + *len] != ','))
			return (0);
		i += *len + 1;
		j++;
	}
	if (j != 3)
		return (0);
	v[j] = w;
	*len = i - 1;
	return (*len);
}
