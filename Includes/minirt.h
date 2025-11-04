/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/04 13:49:44 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"


//scene struct

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_amb_light
{
	double	ratio;
	t_rgb	color;
}	t_amb_light;

typedef struct s_vec
{
	double	x;
	double	z;
	double	y;
}	t_vec;

typedef struct s_camera
{
	t_vec	position;
	t_vec	orientation_vector;
	double	horizontal_field;
}	t_camera;

typedef	struct s_light
{
	t_vec	position; //coordinates of the lightning point
	double	bright_ratio;
	t_rgb  	color;
}	t_light;

typedef	struct s_scene
{
	// mlx_t		mlx;
	// mlx_image_t		*img; those two for the mlx window
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
}				t_scene;


void		erro_msg(char *str, int v);
void		read_from_fd(char *file_name, t_scene *scene);
int			ft_isspace(char c);
double		atod(char *s);
int			is_numeric(char c);
void		set_vector(t_vec *v, int j, double value);
void		set_color(t_rgb *c, int j, int value);
t_amb_light	amb_light(char *line, t_amb_light a);
t_camera	camera(char *line, t_camera c);
t_light		light(char *line, t_light l);


#endif