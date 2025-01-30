/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:45 by nojia             #+#    #+#             */
/*   Updated: 2025/01/30 09:31:52 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

double	get_positive_min(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	else if (a >= 0 && b < 0)
		return (a);
	else if (b >= 0 && a < 0)
		return (b);
	else if (a < b)
		return (a);
	else
		return (b);
}

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
