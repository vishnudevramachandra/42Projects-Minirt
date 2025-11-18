/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2025/11/18 18:29:29 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"

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

typedef double t_tup[4];

typedef struct s_camera
{
	t_tup	position;
	t_tup	orientation_vector;
	double	horizontal_field;
}	t_camera;

typedef	struct s_light
{
	t_tup	position; //coordinates of the lightning point
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
	t_tup	pos;
	double	dia;
	t_rgb	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_tup	pos;
	t_tup	axis;
	double	dia;
	double	height;
	t_rgb	color;
}	t_cylinder;

typedef struct s_plane
{
	t_tup	point;
	t_tup	norm_vec;
	t_rgb	color;
}	t_plane;

typedef enum	e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE,
}	t_obj_type;

typedef struct s_obj
{
	t_obj_type	typ;
	union
	{
		t_cylinder	cy;
		t_plane		pl;
		t_sphere	sp;
	};
}	t_obj;

typedef struct s_mrt {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		*scene;
	t_list		*objs;
	// void			*mlx_ptr;
	// void			*win_ptr;
}	t_mrt;

//everything struct

// typedef struct s_rt
// {
// 	t_mlx	*m;
	
// }	t_rt;



void		erro_msg(char *str, int v);
void		read_from_fd(char *file_name, t_scene *scene, t_list **objs);
int			ft_isspace(char c);
int			len_spaces(char *str);
double		atod(const char *s);
int			is_numeric(char c);
t_amb_light	amb_light(char *line, t_amb_light a);
t_camera	camera(char *line, t_camera c);
t_light		light(char *line, t_light l);
int			ft_strcmp(char *s1, char *s2);
int			get_rgba(t_rgb *c, double a);
void		init_mrt(t_mrt *m);
void		add_tuples(t_tup res, t_tup a, t_tup b);
void		sub_tuples(t_tup res, t_tup a, t_tup b);
void		multi_tuple(t_tup res, t_tup a, double val);
void		div_tuple(t_tup res, t_tup a, double val);
double		dot_prod(t_tup a, t_tup b);
double		magnitude(t_tup a);
void		cross_prod(t_tup res, t_tup a, t_tup b);
void		normalize(t_tup res, t_tup a);

#endif