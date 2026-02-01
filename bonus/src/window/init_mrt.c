/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majkijew <majkijew@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:08:17 by majkijew          #+#    #+#             */
/*   Updated: 2026/02/01 07:15:40 by majkijew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

// void	ft_hook(void *param)
// {
// 	// mlx_key_data_t keydata;
// 	t_mrt	*m;
// 	m = (t_mrt *)param;
// 	if (mlx_is_key_down(m->mlx, MLX_PRESS) ||
//  mlx_is_key_down(m->mlx, MLX_REPEAT))
// 	{	
// 		if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
// 		{
// 			mlx_close_window(m->mlx);
// 			erro_clean(m, "esc", 0);
// 		}
// 		if (mlx_is_key_down(m->mlx, MLX_KEY_UP))
// 			m->image->instances[0].y -= 5;
// 		if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN))
// 			m->image->instances[0].y += 5;
// 		if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
// 			m->image->instances[0].x += 5;
// 		if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
// 			m->image->instances[0].x -= 5;
// 		canvas(m);
// 	}
// }
void	init_motion(t_motion *direct, t_camera *c)
{
	init_vector(direct->ver, 0, 1, 0);
	sub_tuples(direct->forward, c->to, c->position);
	normalize(direct->forward);
	cross_prod(direct->hotizon, direct->forward, direct->ver);
	normalize(direct->forward);
}
// void move_camera(t_camera *c, int key)
// {
// 	t_tup dir;
// 	copy_vector(dir, c->orientation_vector);

// 	t_tup right;
// 	cross_prod(right, c->orientation_vector, c->up);
// 	normalize(right);

// 	if (key == MLX_KEY_UP)
// 	{
// 		multi_tuple(dir, dir, SPEED);
// 		add_tuples(c->position, c->position, dir);
// 		add_tuples(c->to, c->to, dir);
// 	}
// 	else if (key == MLX_KEY_DOWN)
// 	{
// 		multi_tuple(dir, dir, -SPEED);
// 		add_tuples(c->position, c->position, dir);
// 		add_tuples(c->to, c->to, dir);
// 	}
// 	else if (key == MLX_KEY_RIGHT)
// 	{
// 		multi_tuple(right, right, SPEED);
// 		add_tuples(c->position, c->position, right);
// 		add_tuples(c->to, c->to, right);
// 	}
// 	else if (key == MLX_KEY_LEFT)
// 	{
// 		multi_tuple(right, right, -SPEED);
// 		add_tuples(c->position, c->position, right);
// 		add_tuples(c->to, c->to, right);
// 	}
// 	t_mat4 T;
// 	translation_mat(T, move_vec);
// 	translate_objects(m->obj, T);
// 	translate_lights(m->scene->lights_list, T);
// 	// --- DEBUG ---
// void	move_camera(t_camera *c, int key)
// {
// 	t_tup	dir;
	// t_tup right;
// 	copy_vector(dir, c->orientation_vector);
// 	// cross_prod(right, dir, c->up);
// 	if (key == MLX_KEY_UP)
// 	{
// 		multi_tuple(dir, dir, SPEED);
// 		add_tuples(c->position, c->position, dir);
// 	}
// 	// else if (key == MLX_KEY_UP)
// 	// 	cam->position -= dir * SPEED;
// 	// else if (key == MLX_KEY_DOWN))
// 	// 	cam->position -= right * SPEED;
// 	// else if (key == D)
// 	// 	cam->position += right * SPEED;
// 	// else if (key == Q)
// 	// 	cam->position += cam->up * SPEED;
// 	// else if (key == E)
// 	// 	cam->position -= cam->up * SPEED;
// }
#define SPEED 1.0

void	move_camera(t_camera *c, int key)
{
	t_tup	forward;
	t_tup	right;
	t_tup	move_vec;

	sub_tuples(forward, c->to, c->position);
	normalize(forward);
	cross_prod(right, forward, c->up);
	normalize(right);
	init_vector(move_vec, 0, 0, 0);
	if (key == MLX_KEY_UP)
		multi_tuple(move_vec, forward, -SPEED);
	else if (key == MLX_KEY_DOWN)
		multi_tuple(move_vec, forward, SPEED);
	else if (key == MLX_KEY_RIGHT)
		multi_tuple(move_vec, right, SPEED);
	else if (key == MLX_KEY_LEFT)
		multi_tuple(move_vec, right, -SPEED);
	else if (key == MLX_KEY_Q)
		init_vector(move_vec, 0, SPEED, 0);
	else if (key == MLX_KEY_E)
		init_vector(move_vec, 0, -SPEED, 0);
	add_tuples(c->position, c->position, move_vec);
	add_tuples(c->to, c->to, move_vec);
	sub_tuples(c->orientation_vector, c->to, c->position);
	normalize(c->orientation_vector);
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_mrt	*m;

	m = (t_mrt *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		{
			mlx_close_window(m->mlx);
			erro_clean(m, "esc", 0);
		}
		else
		{	
			move_camera(&m->scene->camera, keydata.key);
			setup_viewport(&m->view, m);
			translate_objects_and_lights(m);
			mlx_delete_image(m->mlx, m->image);
			m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
			mlx_image_to_window(m->mlx, m->image, 0, 0);
			canvas(m);
		}
	}
}

void	init_mrt(t_mrt *m)
{
	m->mlx = mlx_init(WIDTH, HEIGHT, "minirt", true);
	if (!m->mlx)
		erro_clean(m, "Error", 2);
	m->image = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	if (!m->image)
	{
		mlx_close_window(m->mlx);
		erro_clean(m, "Error", 2);
	}
	if (mlx_image_to_window(m->mlx, m->image, 0, 0) == -1)
	{
		mlx_close_window(m->mlx);
		erro_clean(m, "Error", 2);
	}
	canvas(m);
	mlx_key_hook(m->mlx, &key_hooks, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
}
