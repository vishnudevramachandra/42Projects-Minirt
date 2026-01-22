/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:32:19 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/22 18:55:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

// suggestion:?
// sp 0,0,8      3   255,0,255 P [colors] [coordinates] [pattern type] 
// sp 0,0,8      3   255,0,255 P 255,255,255 1.3,1.2,0 str

int	check_pattern_type(t_material *mt, char *line)
{
	if (ft_strncmp(line, "str", 3) == 0)
	{
		mt->pattern.fcn = stripped_pattern;
		return (1);
	}
	else if (ft_strncmp(line, "chr", 3) == 0)
	{
		mt->pattern.fcn = checker_pattern;
		return (1);
	}
	else if (ft_strncmp(line, "ring", 4) == 0)
	{
		mt->pattern.fcn = ring_pattern;
		return (1);
	}
	return (0);
}

int	set_pattern(t_material *mt, char *line, int *len)
{
	int	i;

	i = 1;
	if (line[0] == 'P')
	{
		i += len_spaces(line + i);
		if (!set_color(&mt->pattern.color2, line + i, len))
			return (0);
		i += *len;
		i += len_spaces(line + i);
		if (!set_tuple(mt->pattern.param, line + i, len, 0))
			return (0);
		i += *len;
		i += len_spaces(line + i);
		if (!check_pattern_type(mt, line + i))
			return (0);
		while (!ft_isspace(line[i]))
			i++;
		i += len_spaces(line + i);
		mt->shininess = atod(&line[i]);
		return (1);
	}
	mt->shininess = 500;
	return (0);
}
