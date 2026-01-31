/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 00:31:55 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/31 19:16:11 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static int	ft_strspn(const char *s, t_dataype dtype)
{
	int	i;
	int	tmp;

	i = 0;
	if (dtype == INT)
	{
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		return (i);
	}
	i = ft_strspn(s, INT);
	if (i == 0 || s[i] != '.')
		return (0);
	tmp = ft_strspn(s + i + 1, INT);
	if (tmp == 0)
		return (0);
	return (i + 1 + tmp);
}

int	set_int(int *i, const char *s, int *len)
{
	if (s[0] == '-')
	{
		*len = 1 + ft_strspn(s + 1, INT);
		if (*len < 2)
			return (0);
	}
	else
	{
		*len = ft_strspn(s, INT);
		if (*len < 1)
			return (0);
	}
	*i = ft_atoi(s);
	return (*len);
}

int	correct_color_range(int *ptrs)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ptrs[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

int	set_color(t_rgb *c, const char *s, int *len)
{
	int	i;
	int	j;
	int	*ptrs[3];

	ptrs[0] = &c->r;
	ptrs[1] = &c->g;
	ptrs[2] = &c->b;
	i = 0;
	j = 0;
	while (j < 3 && s[i] && s[i] != '\n')
	{
		set_int(ptrs[j], s + i, len);
		if (!*len || (j < 2 && s[i + *len] != ','))
			return (0);
		i += *len + 1;
		j++;
	}
	if (j != 3)
		return (0);
	*len = i - 1;
	if (!correct_color_range(*ptrs))
		return (0);
	return (*len);
}
