/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:19:54 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/05 17:52:44 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

static int	strspn(const char *s, t_dataype dtype)
{
	int		i;
	int		tmp;
	const char	charset[] = "0123456789";

	i = 0;
	if (dtype == INT)
	{
		while (s[i])
		{
			if (!ft_strchr(charset, s[i]))
				break ;
			i++;
		}
	}
	else
	{
		i = strspn(s + i, INT);
		if (!i || (s[i] != '.'))
			return (0);
		tmp = strspn(s + i + 1, INT);
		if (!tmp)
			return (0);
		i += 1 + tmp;
	}
	return (i);
}

int	set_double(double *d, const char *s)
{
	int	len;

	len = strspn(s, DOUBLE);
	if (len < 1)
		return (len);
	*d = atod(s);
	return (len);
}

int	set_vector(t_vec *v, const char *s)
{
	int		i;
	int		j;
	int		len;
	double	*ptrs[3];

	ptrs[0] = &v->x;
	ptrs[1] = &v->y;
	ptrs[2] = &v->z;
	i = 0;
	j = 0;
	while (j < 3 && s[i] && s[i] != '\n')
	{
		len = set_double(ptrs[j], s + i);
		if (!len || (j < 2 && s[i + len] != ','))
			return (0);
		i += len + 1;
		j++;
	}
	if (j != 3)
		return (0);
	return (i - 1);
}

int	set_int(int *i, const char *s)
{
	int	len;

	len = strspn(s, INT);
	if (len < 1)
		return (len);
	*i = ft_atoi(s);
	return (len);
}

int	set_color(t_rgb *c, const char *s)
{
	int	i;
	int	j;
	int	len;
	int	*ptrs[3];

	ptrs[0] = &c->r;
	ptrs[1] = &c->g;
	ptrs[2] = &c->b;
	i = 0;
	j = 0;
	while (j < 3 && s[i] && s[i] != '\n')
	{
		len = set_int(ptrs[j], s + i);
		if (!len || (j < 2 && s[i + len] != ','))
			return (0);
		i += len + 1;
		j++;
	}
	if (j != 3)
		return (0);
	return (i - 1);
}
