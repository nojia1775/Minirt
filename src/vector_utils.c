/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:06:21 by yrio              #+#    #+#             */
/*   Updated: 2025/01/09 21:02:11 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple *create_tuple(double x, double y, double z, int w)
{
	t_tuple *vec;

	vec = malloc(sizeof(t_tuple));
	if (!vec)
		return (NULL);
	vec->coor[0] = x;
	vec->coor[1] = y;
	vec->coor[2] = z;
	vec->coor[3] = w;
	return (vec);
}

t_tuple	create_tuple2(double x, double y, double z, int w)
{
	t_tuple	vec;

	vec.coor[0] = x;
	vec.coor[1] = y;
	vec.coor[2] = z;
	vec.coor[3] = w;
	return (vec);
}

t_tuple	get_pixel_tuple(t_minirt *minirt, int x, int y)
{
	t_tuple	U;
	t_tuple	V;
	t_tuple	normal_v_cam;
	t_tuple	pixel;
	double		x_screen;
	double		y_screen;

	normal_v_cam = vec_normalization2(minirt->camera->tuple_xyz);
	t_canva transform = rotation_y(PI / 2);
	// if (double_abs(normal_v_cam.coor[0]) <= 0.1
	// 	&& double_abs(normal_v_cam.coor[1]) >= 0.9 && double_abs(normal_v_cam.coor[2]) <= 0.1)
	// 	U = vec_normalization2(vec_cross(create_tuple2(0, 0, 1, 0), normal_v_cam));
	// else
	// 	U = vec_normalization2(vec_cross(create_tuple2(0, 1, 0, 0), normal_v_cam));
	U = vec_normalization2(multiplying_matrix_tuple(transform, normal_v_cam));
	V = vec_normalization2(vec_cross(normal_v_cam, U));
	x_screen = ((double)x / WIDTH - 0.5) * WIDTH;
	y_screen = (0.5 - (double)y / HEIGHT) * HEIGHT;
	pixel.coor[0] = normal_v_cam.coor[0] * minirt->camera->focal_length
		+ U.coor[0] * x_screen + V.coor[0] * y_screen;
	pixel.coor[1] = normal_v_cam.coor[1] * minirt->camera->focal_length
		+ U.coor[1] * x_screen + V.coor[1] * y_screen;
	pixel.coor[2] = normal_v_cam.coor[2] * minirt->camera->focal_length
		+ U.coor[2] * x_screen + V.coor[2] * y_screen;
	return (vec_normalization2(pixel));
}

t_tuple reflect(t_tuple in, t_tuple normal)
{
	return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in, normal))));
}