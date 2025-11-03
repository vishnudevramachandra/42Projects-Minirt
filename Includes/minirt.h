/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/03 15:18:26 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

void	erro_msg(char *str, int v);
void	read_from_fd(char *file_name);
int		ft_isspace(char c);
double	atod(char *s);


//scene struct
typedef struct s_amb_light
{
	double	ratio;
	int		colors[3];
}			t_amb_light;

typedef struct s_vec
{
	double	x;
	double	z;
	double	y;
}			t_vec;

typedef struct s_camera
{
	t_vec	orintation_vector;
	t_vec	position;
	double	horizontal_field;
}				t_camera;

typedef	struct s_light
{
	t_vec	cord_light; //coordinates of the lightning point
	double	bright_ratio;
	int		colors[3];
}				t_light;

typedef	struct s_scene_data
{
	// mlx_t		mlx;
	// mlx_image_t		*img; those two for the mlx window
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
}				t_scene_data;

#endif