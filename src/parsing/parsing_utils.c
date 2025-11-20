/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:19:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/20 16:52:54 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static int	ft_strspn(const char *s, t_dataype dtype)
{
	int		i;
	int		tmp;
	const char	charset[] = "0123456789";

	if (dtype == INT)
	{
		i = 0;
		if (s[i] && s[i + 1])
		while (s[i])
		{
			if (!ft_strchr(charset, s[i]))
				break ;
			i++;
		}
	}
	else
	{
		i = ft_strspn(s, INT);
		if (!i || (s[i] != '.'))
			return (0);
		tmp = ft_strspn(s + i + 1, INT);
		if (!tmp)
			return (0);
		i += 1 + tmp;
	}
	return (i);
}

int	set_double(double *d, const char *s, int *len)
{
	int	i;

	i = 0;
	if (s[0] == '-')
	{
		while ('0' <= *(s + 1 + i) && *(s + 1 + i) <= '9')
			i++;
		if (*(s + 1 + i) == '.')
			*len = 1 + ft_strspn(s + 1, DOUBLE);
		else
			*len = 1 + ft_strspn(s + 1, INT);
		if (*len < 2)
			return (0);
	}
	else
	{
		while ('0' <= *(s + i) && *(s + i) <= '9')
			i++;
		if (*(s + i) == '.')
			*len = ft_strspn(s, DOUBLE);
		else
			*len = ft_strspn(s, INT);
		if (*len < 1)
			return (0);
	}
	*d = atod(s);
	return (*len);
}

int	set_vector(t_tup *v, const char *s, int *len)
{
	int		i;
	int		j;
	double	*ptrs[3];

	// ptrs[0] = &v->x;
	// ptrs[1] = &v->y;
	// ptrs[2] = &v->z;
	// v->w = 0;
	i = 0;
	j = 0;
	while (j < 3 && s[i] && s[i] != '\n')
	{
		set_double(ptrs[j], s + i, len);
		if (!*len || (j < 2 && s[i + *len] != ','))
			return (0);
		i += *len + 1;
		j++;
	}
	if (j != 3)
		return (0);
	*len = i - 1;
	return (*len);
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
	return (*len);
}
