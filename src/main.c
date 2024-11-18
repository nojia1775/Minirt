/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 17:08:18 by yrio             ###   ########.fr       */
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

int main(void)
{
	t_shape		sphere;
	t_matrix	mat;

	sphere = create_sphere(5);
	printf("in main %p\n", sphere.mat->array);
	mat = *sphere.mat;
	display_mat2d(&mat, 1, 2, 5);
	return (0);
}
