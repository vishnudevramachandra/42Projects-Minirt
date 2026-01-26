/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2026/01/25 18:42:01 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

#define EPSILON 1e-4

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

typedef double	t_tup[4];

typedef struct s_ray
{
	t_tup	origin;
	t_tup	direction;
}	t_ray;

typedef struct s_camera
{
	t_tup	position;
	t_tup	orientation_vector;
	double	horizontal_field;
}	t_camera;

typedef struct s_light
{
	t_tup	position; //coordinates of the lightning point
	double	bright_ratio;
	t_rgb	color;
}	t_light;

typedef struct s_scene
{
	// mlx_t		mlx;
	// mlx_image_t		*img; those two for the mlx window
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
}				t_scene;

typedef t_rgb*(*t_pattern_fcn)(t_tup param, t_rgb *c1, t_rgb *c2,
	t_tup hit_point);

typedef struct s_pattern
{
	t_tup			param;
	t_rgb			color1;
	t_rgb			color2;
	t_pattern_fcn	fcn;
}	t_pattern;

typedef struct s_material
{
	double		shininess;
	t_pattern	pattern;
}	t_material;

typedef struct s_sphere
{
	t_material	mt;
	t_tup		pos; //center
	double		dia; //radious
}	t_sphere;

typedef struct s_cylinder
{
	t_material	mt;
	t_tup		pos;
	t_tup		axis;
	double		dia;
	double		height;
}	t_cylinder;

typedef struct s_plane
{
	t_material	mt;
	t_tup		point;
	t_tup		norm_vec;
}	t_plane;

typedef enum e_obj_type
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

typedef struct s_inter
{
	double			t;
	t_obj			*obj;
	t_tup			hit_point;
	t_tup			scaled;
	t_tup			normal;	
	struct s_inter	*next;
}	t_inter;

typedef double	mat4[4][4];

typedef struct s_cam_inv
{
	mat4	trsl;
	mat4	proj;
	mat4	final;
}	t_cam_inv;

typedef struct s_mrt
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		*scene;
	t_list		*obj;
	t_ray		ray;
	t_inter		*i;
	t_cam_inv	inv;
	// t_ray		*ray;
	// void			*mlx_ptr;
	// void			*win_ptr;
}	t_mrt;

typedef struct s_view
{
	double	px_width;
	double	h_start_pos;
	double	v_start_pos;
}	t_view;

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
void		cross_prod(t_tup res, t_tup a, t_tup b);
double		dot_prod(t_tup a, t_tup b);
double		magnitude(t_tup a);
void		normalize(t_tup a);
void		multi_and_accum_tuple(t_tup res, t_tup a, double val);
void		multi_mat_mat(mat4 res, mat4 a, mat4 b);
void		multi_mat_tuple(t_tup res, mat4 m, t_tup t);
void		transpose_mat(mat4 m);
bool		is_equal_tup(t_tup a, t_tup b);
bool		is_equal_mat(mat4 a, mat4 b);
mat4		*copy_mat(mat4 new, mat4 old);
mat4		*identity_mat(mat4 m);
mat4		*translation_mat(mat4 m, double d[3]);
mat4		*scaling_mat(mat4 m, double d[3]);
mat4		*rotation_mat(mat4 m, double angles[3]);
mat4		*shearing_mat(mat4 m, double angles[6]);
void		init_vector(t_tup vec, double x, double y, double z);
void		init_point(t_tup vec, double x, double y, double z);
void		copy_vector(t_tup new, t_tup old);
void		copy_point(t_tup new, t_tup old);
void		copy_tup(t_tup new, t_tup old);
void		create_ray(t_ray *ray, t_tup point, t_tup vector);
int			rgb(int a, int b, int c, int d);
double		inter_sphere(t_sphere *sp, t_ray *r);
double		inter_plane(t_plane *pl, t_ray *r);
double		inter_cylinder(t_cylinder *cy, t_ray *r);
double		delta(double a, double b_h, double c);
double		get_hitpoint(double a, double b_h, double sqrt_dlt);
void		project_point_on_vector(t_tup res, t_tup center_to_hit, t_tup vec);
void		compute_cy_normal(t_tup normal, t_tup hit_point, t_cylinder *cy);
t_tup		*perpvec_to_plane(t_tup vec, t_plane *pl, t_tup origin);
void		print_tup(t_tup vec);
void		normal_at(t_tup normal, t_obj *obj, t_tup hit_point);
void		canvas(t_mrt *m);
void		render_light(t_mrt *m, uint32_t *x, uint32_t *y);
void		mult_scalar_colors(t_rgb *new_c, t_rgb *old_c, double scalar);
void		multi_colors(t_rgb	*c_new, t_rgb *c1, t_rgb *c2);
void		reflect(t_tup out, t_tup in, t_tup normal);
void		translate_objects(t_mrt *m);
void		project_objects(t_mrt *m);
void		calc_direction(t_camera *cam, t_view *view, int x, int y);
void		setup_viewport(t_view *view, t_mrt *m);
void		add_colors(t_rgb *new_c, t_rgb *c1, t_rgb *c2);
void		add_to_color(t_rgb *new_c, t_rgb *c1, double comp);
t_rgb		*stripped_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point);
t_rgb		*ring_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point);
t_rgb		*checker_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point);

#endif