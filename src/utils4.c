/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/24 11:50:55 by nojia            ###   ########.fr       */
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
	t_tuple	result_world;
	t_tuple	*normalized_result_world;

	result_world = vec_sub_vec2(world_point, sphere.xyz);
	normalized_result_world = vec_normalization(&result_world);
	return (*normalized_result_world);
}
