/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:55:21 by majkijew          #+#    #+#             */
/*   Updated: 2026/02/01 00:18:08 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define EPSILON 1e-4

# define MINIRT_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../get_next_line/get_next_line.h"
# include "mlx.h"

typedef struct s_obj	t_obj;
typedef double			t_mat4[4][4];
typedef double			t_tup[4];
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef t_rgb			*(*t_pattern_fcn)(t_tup param, t_rgb *c1, t_rgb *c2,
	t_tup hit_point);

typedef struct s_amb_light
{
	int		count;
	double	ratio;
	t_rgb	color;
}	t_amb_light;

typedef struct s_ray
{
	t_tup	origin;
	t_tup	direction;
}	t_ray;

typedef struct s_camera
{
	int		count;
	t_tup	position;
	t_tup	orientation_vector;
	double	horizontal_field;
}	t_camera;

typedef struct s_light
{
	t_tup	position;
	double	bright_ratio;
	t_rgb	color;
}	t_light;

typedef struct s_scene
{
	t_amb_light	amb_light;
	t_camera	camera;
	t_list		*lights_list;
}	t_scene;

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
	t_tup		pos;
	double		dia;
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
	double			t0;
	double			t1;
	t_obj			*obj;
	t_tup			hit_point;
	t_tup			scaled;
	t_tup			normal;	
	struct s_inter	*next;
}	t_inter;

typedef struct s_cam_inv
{
	t_mat4	trsl;
	t_mat4	proj;
	t_mat4	final;
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
}	t_mrt;

typedef struct s_view
{
	double	px_width;
	double	h_start_pos;
	double	v_start_pos;
}	t_view;

void		check_arguments(int ac, char **av);
void		init_scene(t_scene *scene);
void		erro_msg(char *str, int v);
int			read_from_fd(char *file_name, t_scene *scene, t_list **objs);
int			ft_isspace(char c);
int			len_spaces(char *str);
double		atod(const char *s);
int			is_numeric(char c);
int			amb_light(char *line, t_amb_light *a);
int			camera(char *line, t_camera *c);
t_light		*light_f(char *line, t_light *l);
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
t_mat4		*multi_mat_mat(t_mat4 res, t_mat4 a, t_mat4 b);
t_tup		*multi_mat_tuple(t_tup res, t_mat4 m, t_tup t);
void		transpose_mat(t_mat4 m);
bool		is_equal_tup(t_tup a, t_tup b);
bool		is_equal_mat(t_mat4 a, t_mat4 b);
t_mat4		*copy_mat(t_mat4 new, t_mat4 old);
t_mat4		*identity_mat(t_mat4 m);
t_mat4		*translation_mat(t_mat4 m, double d[3]);
t_mat4		*scaling_mat(t_mat4 m, double d[3]);
t_mat4		*rotation_mat(t_mat4 m, double angles[3]);
t_mat4		*shearing_mat(t_mat4 m, double angles[6]);
void		init_vector(t_tup vec, double x, double y, double z);
void		init_point(t_tup vec, double x, double y, double z);
void		copy_vector(t_tup new, t_tup old);
void		copy_point(t_tup new, t_tup old);
void		copy_tup(t_tup new, t_tup old);
void		create_ray(t_ray *ray, t_tup point, t_tup vector);
int			rgb(int a, int b, int c, int d);
void		color_range(t_rgb *c);
void		inter_sphere(double *t, t_sphere *sp, t_ray *r);
void		inter_plane(double *t, t_plane *pl, t_ray *r);
void		inter_cylinder(double *t, t_cylinder *cy, t_ray *r);
void		inter_obj(double *t, t_obj *obj, t_ray *ray);
double		delta(double a, double b_h, double c);
void		get_hitpoints(double *t, double a, double b_h, double sqrt_dlt);
void		project_point_on_vector(t_tup res, t_tup center_to_hit, t_tup vec);
void		compute_cy_normal(t_tup normal, t_tup hit_point, t_cylinder *cy);
t_tup		*perpvec_to_plane(t_tup vec, t_plane *pl, t_tup origin);
void		normal_at(t_tup normal, t_obj *obj, t_tup hit_point);
void		insert_intersection(t_inter **list, t_inter *new,
				t_obj *obj, double *t);
void		compute_intersections(t_inter **inter, t_mrt *m);
void		free_list(t_inter *i);
void		canvas(t_mrt *m);
void		mult_scalar_colors(t_rgb *new_c, t_rgb *old_c, double scalar);
void		multi_colors(t_rgb	*c_new, t_rgb *c1, t_rgb *c2);
void		reflect(t_tup out, t_tup in, t_tup normal);
void		normalize_vectors(t_mrt *m);
void		translate_objects_and_lights(t_mrt *m);
void		project_objects_and_lights(t_mrt *m);
void		calc_direction(t_camera *cam, t_view *view, int x, int y);
void		setup_viewport(t_view *view, t_mrt *m);
void		add_colors(t_rgb *new_c, t_rgb *c1, t_rgb *c2);
void		add_to_color(t_rgb *new_c, t_rgb *c1, double comp);
t_rgb		*stripped_pattern(t_tup param, t_rgb *c1, t_rgb *c2,
				t_tup hit_point);
t_rgb		*ring_pattern(t_tup param, t_rgb *c1, t_rgb *c2, t_tup hit_point);
t_rgb		*checker_pattern(t_tup param, t_rgb *c1, t_rgb *c2,
				t_tup hit_point);
int			create_node_and_add_to_list(void *content, t_list **lst);
void		final_obj_color(t_rgb *final_col, t_mrt *m, t_inter *i);
int			is_object(char *line);
int			is_scene(char *line);
bool		verify_id(char *line);
char		*get_identifier(char *line);
bool		scene_range(t_amb_light a, t_camera c);
void		find_obj_color(t_rgb *obj_c, t_inter *i);
void		find_tex_color(t_rgb **obj_col, t_mrt *m, t_inter *i);
int			is_in_shadow(t_mrt *m, t_inter *hit,
				t_tup light_unit_vec, double light_dist);
void		scale_u_v(int *u, int *v, double *uv, uint32_t *height_width);
void		bump_the_normal(t_inter *i, double *uv);
void		erro_clean(t_mrt *mrt, char *str, int v);
void		check_for_texture(t_rgb	**obj_c, double	*shininess,
				t_mrt *m, t_inter *i);
void		compute_light_unit_vec(t_tup light_unit_vec, double *light_dist,
				t_light *light, t_inter *hit);

#endif