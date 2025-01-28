/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2025/01/28 13:57:17 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

// int	main(int argc, char **argv, char **env)
// {
// 	if (!parsing(argc, argv, env))
// 		return (printf("Error\n"), 1);
// 	return (0);
// }

// int	main(void)
// {
// 	t_vector	*vec;
// 	t_vector	*vec2;
// 	double		result;
	
// 	vec = NULL;
// 	vec2 = NULL;
// 	vec = create_vector(1, 3, 2, 0);
// 	vec2 = create_vector(2, 1, 4, 0);
// 	result = dot_product(vec, vec2, 3);
// 	printf("result : %f\n", result);
// 	//printf("x : %f, y : %f, z : %f\n", vec->coor[0], vec->coor[1], vec->coor[2]);
// 	return (1);
// }

// int main(void)
// {
// 	t_matrix mat;

// 	mat = create_matrix(10, 10, 10);
// 	display_mat2d(&mat, 1, 2, 0);
// 	return (0);
// }

static int	close_win(void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	free_minirt(minirt);
	exit(0);
	return (1);
}

static int	key_pressed(int key, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (key == ESC)
		close_win(minirt);
	else if (key == A_RIGHT)
		cam_go_leftright(minirt, 1);
	else if (key == A_LEFT)
		cam_go_leftright(minirt, -1);
	else if (key == A_UP)
		cam_go_frontback(minirt, 1);
	else if (key == A_DOWN)
		cam_go_frontback(minirt, -1);
	else if (key == UP)
		cam_look_updown(minirt, -PI / 8.0);
	else if (key == DOWN)
		cam_look_updown(minirt, PI / 8.0);
	else if (key == LEFT)
		cam_look_leftright(minirt, -PI / 8.0);
	else if (key == RIGHT)
		cam_look_leftright(minirt, PI / 8.0);
	else if (key == TAB)
		cam_go_updown(minirt, -1);
	else if (key == SPACE)
		cam_go_updown(minirt, 1);
	else if (key == P)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		display_precision(minirt);
	}
	return (1);
}

void	init_minirt(t_minirt *minirt)
{
	minirt->ambient = NULL;
	minirt->camera = NULL;
	minirt->cylinder = NULL;
	minirt->light = NULL;
	minirt->plan = NULL;
	minirt->sphere = NULL;
	minirt->mlx = NULL;
	minirt->win = NULL;
	minirt->addr_img = NULL;
	minirt->img = NULL;
	minirt->bits = 0;
	minirt->size_line = 0;
	minirt->color = 0.0;
}

int	main(int argc, char **argv, char **env)
{
	t_minirt	minirt;

	init_minirt(&minirt);
	if (!parsing(argc, argv, env, &minirt))
		return (free_minirt(&minirt), 1);
	my_mlx_init(&minirt);
	my_mlx_new_window(&minirt, WIDTH, HEIGHT, "MINIRT");
	mlx_hook(minirt.win, 17, 0, close_win, &minirt);
	mlx_key_hook(minirt.win, key_pressed, &minirt);
	my_mlx_new_img(&minirt);
	display_precision(&minirt);
	printf("done\n");
	mlx_loop(minirt.mlx);
	free_minirt(&minirt);
	return (0);
}

// int	main(void)
// {
// 	// test_multiply_matrix();
// 	// test_multiply_matrix_4X4_by_tuple();
// 	// transposing_matrix_4X4();
// 	// test_determinant_2X2_matrix();
// 	// test_submatrix_of_3X3_matrix();
// 	// test_submatrix_of_4X4_matrix();
// 	// test_minor_3X3_matrix();
// 	// test_cofactor_3X3_matrix();
// 	// test_determinant_3X3_matrix();
// 	// test_determinant_of_4X4_matrix();
// 	// test1_invert_4X4_matrix();
// 	// test_multiply_product_by_inverse();
// 	test_translation_matrix();
// 	// test_scaling_matrix();
// 	// test_rotation_matrix();
// 	// test_shearing_matrix();
// 	// test_chaining_matrix();
// 	test_normal_at_sphere();
// 	//test_reflect_function();
// 	test_lighting_function();
// 	test_rayon_position();
// 	test_intersection_sphere();
// 	test_encapsulates_t_shape();
// 	test_hit_function();
// 	test_transform_ray();
// 	test_transformation_sphere_operation();

// 	return (0);
// }

// int	main(void)
// {
// 	t_tuple			*position;
// 	t_tuple			*velocity;
// 	t_tuple			*gravity;
// 	t_tuple			*wind;
// 	t_projectile	*proj;
// 	t_environment	*env;
// 	int				count;

// 	position = create_tuple(0, 1, 0, 1);
// 	velocity = vec_normalization(create_tuple(2, 2, 0, 0));
// 	proj = create_projectile(position, velocity);
// 	gravity = create_tuple(0, -0.1, 0, 0);
// 	wind = create_tuple(-0.01, 0, 0, 0);
// 	env = create_environment(gravity, wind);
// 	printf("projectile position : %f , %f , %f | velocity : %f , %f , %f\n", 
// 		proj->position->coor[0], proj->position->coor[1], proj->position->coor[2], proj->velocity->coor[0],
// 		proj->velocity->coor[1], proj->velocity->coor[2]);
// 	count = 0;
// 	while (count < 20)
// 	{
// 		proj = tick(env, proj);
// 		printf("projectile position : %f , %f , %f | velocity : %f , %f , %f\n", 
// 			proj->position->coor[0], proj->position->coor[1], proj->position->coor[2], proj->velocity->coor[0],
// 			proj->velocity->coor[1], proj->velocity->coor[2]);
// 		count++;
// 	}
// }