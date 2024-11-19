/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/18 20:13:16 by yrio             ###   ########.fr       */
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

// static int	close_win(void *param)
// {
// 	t_minirt	*minirt;
	
// 	minirt = (t_minirt *)param;
// 	free_minirt(minirt);
// 	exit(0);
// 	return (1);
// }

// static int	key_pressed(int key, void *param)
// {
// 	t_minirt	*minirt;

// 	minirt = (t_minirt *)param;
// 	if (key == ESC)
// 		close_win(minirt);
// 	return (1);
// }

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
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_minirt	minirt;
// 	int			width;
// 	int			height;

// 	width = 900;
// 	height = 550;
// 	init_minirt(&minirt);
// 	if (!parsing(argc, argv, env, &minirt))
// 		return (free_minirt(&minirt), 1);
// 	my_mlx_init(&minirt);
// 	my_mlx_new_window(&minirt, width, height, "MINIRT");
// 	mlx_hook(minirt.win, 17, 0, close_win, &minirt);
// 	mlx_key_hook(minirt.win, key_pressed, &minirt);
// 	put_pixel_projectile(&minirt, height, 45, 23, 210);
// 	// put_one_color(&minirt, 45, 23, 210);
// 	mlx_loop(minirt.mlx);
// 	free_minirt(&minirt);
// 	return (0);
// }

int	main(void)
{
	t_canva	can;

	can = create_canva(2, 2);
	can.array[0][0] = 1;
	can.array[0][1] = 5;
	can.array[1][0] = -3;
	can.array[1][1] = 2;

	printf("determinant : %d\n", get_determinant_2X2_matrix(can));
	//pixel = create_tuple(220, 23, 15, 2);
	//printf("width : %d, height : %d\n", can.shape[0], can.shape[1]);
	return (0);
}

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
