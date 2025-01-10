/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:45 by nojia             #+#    #+#             */
/*   Updated: 2025/01/10 11:31:04 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	print_coor(void *coor)
{
	t_tuple	*vec;

	vec = (t_tuple *)coor;
	printf("%f %f %f\n", vec->coor[0], vec->coor[1], vec->coor[2]);
}

t_tuple	negate_tuple(t_tuple tuple)
{
	tuple.coor[0] = -tuple.coor[0];
	tuple.coor[1] = -tuple.coor[1];
	tuple.coor[2] = -tuple.coor[2];
	return (tuple);
}

t_tuple	normal_tuple_sphere(t_shape sphere, t_tuple world_point)
{
	t_canva inv_can = inverse_matrix_4X4(sphere.transform);
	t_tuple result =  multiplying_matrix_tuple(inv_can, world_point);
	t_canva transpose_inv_can = transpose_4X4_matrix(inv_can);
	t_tuple result_world = multiplying_matrix_tuple(transpose_inv_can, result);
	result_world.coor[3] = 0;
	t_tuple *normalized_result_world = vec_normalization(&result_world);
	return (*normalized_result_world);
}