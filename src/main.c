/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 16:17:13 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// int	main(int argc, char **argv, char **env)
// {
// 	if (!parsing(argc, argv, env))
// 		return (printf("Error\n"), 1);
// 	return (0);
// }

int	main(void)
{
	t_vector	*vec;
	t_vector	*vec2;
	double		result;
	
	vec = NULL;
	vec2 = NULL;
	vec = create_vector(1, 3, 2);
	vec2 = create_vector(2, 1, 4);
	result = dot_product(vec, vec2, 3);
	printf("result : %f\n", result);
	//printf("x : %f, y : %f, z : %f\n", vec->coor[0], vec->coor[1], vec->coor[2]);
	return (1);
}
