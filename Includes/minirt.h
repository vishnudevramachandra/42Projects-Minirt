/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/05 17:30:10 by vramacha         ###   ########.fr       */
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

typedef struct s_sphere
{
	t_vec	pos;
	double	dia;
	t_rgb	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	axis;
	double	dia;
	double	height;
	t_rgb	color;
}	t_cylinder;

typedef struct s_plane
{
	t_vec	point;
	t_vec	norm_vec;
	t_rgb	color;
}	t_plane;

typedef	enum	e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE,
}	t_obj_type;

typedef	struct s_obj
{
	t_obj_type	typ;
	union
	{
		t_cylinder	cy;
		t_plane		pl;
		t_sphere	sp;
	};
}	t_obj;

void		erro_msg(char *str, int v);
void		read_from_fd(char *file_name, t_scene *scene, t_list **objs);
int			ft_isspace(char c);
int			len_spaces(char *str);
double		atod(const char *s);
int			is_numeric(char c);
int			set_vector(t_vec *v, const char *s);
int			set_color(t_rgb *c, const char *s);
int			set_double(double *d, const char *s);
int			set_int(int *i, const char *s);
t_amb_light	amb_light(char *line, t_amb_light a);
t_camera	camera(char *line, t_camera c);
t_light		light(char *line, t_light l);
t_list		*parse_obj(char *line, t_list **objs);
void		print_obj(t_list *objs);

#endif