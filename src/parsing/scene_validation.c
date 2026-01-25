/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:20:27 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 16:08:50 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	scene_range(t_amb_light a, t_camera c)
{
	if (a.ratio < 0 || a.ratio > 1)
		return (false);
	else if ((a.color.r < 0 || a.color.r > 255) || (a.color.g < 0
			|| a.color.g > 255) || (a.color.b < 0 || a.color.b > 255))
		return (false);
	else if ((*c.orientation_vector < -1 || *c.orientation_vector > 1))
		return (false);
	else if (c.horizontal_field < 0 || c.horizontal_field > 180)
		return (false);
	else
		return (true);
}

char	*get_identifier(char *line)
{
	int		i;
	int		start;
	int		len;
	char	*id;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (NULL);
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	len = i - start;
	id = malloc(len + 1);
	if (!id)
		return (NULL);
	ft_strlcpy(id, line + start, len + 1);
	id[len] = '\0';
	return (id);
}

bool	verify_id(char *line)
{
	char	*id;
	bool	valid;

	valid = false;
	id = get_identifier(line);
	if (!id)
		return (false);
	if (ft_strcmp(id, "A") == 0
		|| ft_strcmp(id, "C") == 0
		|| ft_strcmp(id, "L") == 0
		|| ft_strcmp(id, "sp") == 0
		|| ft_strcmp(id, "pl") == 0
		|| ft_strcmp(id, "co") == 0
		|| ft_strcmp(id, "cy") == 0)
		valid = true;
	free(id);
	return (valid);
}

int	is_scene(char *line)
{
	if ((line[0] == 'A' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'L' && line[1] == ' '))

		return (1);
	return (0);
}

int	is_object(char *line)
{
	if ((line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		|| (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		|| (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		|| (line[0] == 'c' && line[1] == 'o' && line[2] == ' '))
		return (1);
	return (0);
}
