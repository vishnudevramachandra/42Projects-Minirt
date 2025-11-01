/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:16:44 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/01 21:11:07 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	is_numeric(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	return (0);
}
//separete for ratio and color add valuse to the struct (first make the 
//struct ofc and add check if the values are in the range)

void	amb_light(char *line)
{
	int		i;
	double	ratio;
	int		color[3];
	int		j;

	j = 0;
	i = 0;
	while (line[i] != '\n' && ft_isspace(line[i]))
		i++;
	ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	while (ft_isspace(line[i]))
		i++;
	while (j < 3 && line[i])
	{
		color[j] = ft_atoi(&line[i]);
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	// printf("ratio value: %g\n", ratio);
	// printf("color: R=%d, G=%d, B=%d\n", color[0], color[1], color[2]);
}

void	camera(char *line)
{
	double	view_point[3];
	double	orient_vec[3];
	double	horizontal_view;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		view_point[j] = atod(&line[i]);
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.'
			|| line[i] == '-' || line[i] == '+')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	j = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		orient_vec[j] = atod(&line[i]);
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	horizontal_view = atod(&line[i]);
// line[i] && line[i] != '\n'
	// printf("view point: %g,%g,%g\n", view_point[0], view_point[1], view_point[2]);
	// printf("orient vector %g,%g,%g\n", orient_vec[0], orient_vec[1], orient_vec[2]);
	// printf("horiz: %g\n", horizontal_view);
}

void	light(char *line)
{
	double	light_cords[3];
	double	brig_ratio;
	int		colors[3];
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	while (j < 3 && line[i] && line[i] != '\n')
	{
		light_cords[j] = atod(&line[i]);
		while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.'
			|| line[i] == '-' || line[i] == '+')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	while (ft_isspace(line[i])) //idk if isspace here is not kinda redundant
		i++;
	brig_ratio = atod(&line[i]);
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
		i++;
	j = 0;
	while (j < 3 && line[i])
	{
		colors[j] = ft_atoi(&line[i]);
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ',')
			i++;
		j++;
	}
	// printf("light coordinates %g,%g,%g\n", light_cords[0], light_cords[1], light_cords[2]);
	// printf("brightness ratio: %g\n", brig_ratio);
	// printf("color: R=%d, G=%d, B=%d\n", colors[0], colors[1], colors[2]);
}

void	read_from_fd(char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		erro_msg("ERROR", 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i])
		{
			// printf("lines: %s\n", line);
			if (line[i] == 'A')
			{	
				i++;
				amb_light(line + i);
			}
			else if (line[i] == 'C')
			{
				i++;
				camera(line + i);
			}
			else if (line[i] == 'L')
			{
				i++;
				light(line + i);
			}
			// else
			// 	geo_figures(line[i]);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
