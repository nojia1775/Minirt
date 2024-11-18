/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/18 15:52:38 by yrio             ###   ########.fr       */
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

// int main(void)
// static int	close_win(void *param)
// {
// 	t_minirt	*minirt;
	
// 	minirt = (t_minirt *)param;
// 	free_minirt(minirt);
// 	exit(0);
// 	return (1);
// }

static int	key_pressed(int key, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (key == ESC)
		close_win(minirt);
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
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_minirt	minirt;

// 	init_minirt(&minirt);
// 	if (!parsing(argc, argv, env, &minirt))
// 		return (free_minirt(&minirt), 1);
// 	my_mlx_init(&minirt);
// 	my_mlx_new_window(&minirt, WIDTH, HEIGHT, "MINIRT");
// 	mlx_hook(minirt.win, 17, 0, close_win, &minirt);
// 	mlx_key_hook(minirt.win, key_pressed, &minirt);
// 	display(&minirt);
// 	mlx_loop(minirt.mlx);
// 	free_minirt(&minirt);
// 	return (0);
// }
