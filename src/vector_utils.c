/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:06:21 by yrio              #+#    #+#             */
/*   Updated: 2025/01/17 17:34:22 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	*create_tuple(double x, double y, double z, int w)
{
	t_tuple	*vec;

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

t_tuple	get_pixel_tuple(t_minirt *minirt, t_tuple pixel, int x, int y)
{
	t_tuple	u;
	t_tuple	v;
	t_tuple	normal_v_cam;
	t_canva	transform;
	double	x_y_screen[2];

	normal_v_cam = vec_normalization2(minirt->camera->vector_xyz);
	t_canva transform = rotation_y(PI / 2);
	// if (double_abs(normal_v_cam.coor[0]) <= 0.1
	// 	&& double_abs(normal_v_cam.coor[1]) >= 0.9 && double_abs(normal_v_cam.coor[2]) <= 0.1)
	// 	U = vec_normalization2(vec_cross(create_tuple2(0, 0, 1, 0), normal_v_cam));
	// else
	// 	U = vec_normalization2(vec_cross(create_tuple2(0, 1, 0, 0), normal_v_cam));
	U = vec_normalization2(multiplying_matrix_tuple(transform, normal_v_cam));
	V = vec_normalization2(vec_cross(normal_v_cam, U));
	// U = vec_normalization2(vec_cross(V, normal_v_cam));
	x_screen = ((double)x / WIDTH - 0.5) * WIDTH;
	y_screen = (0.5 - (double)y / HEIGHT) * HEIGHT;
	pixel.coor[0] = normal_v_cam.coor[0] * minirt->camera->focal_length
		+ u.coor[0] * x_y_screen[0] + v.coor[0] * x_y_screen[1];
	pixel.coor[1] = normal_v_cam.coor[1] * minirt->camera->focal_length
		+ u.coor[1] * x_y_screen[0] + v.coor[1] * x_y_screen[1];
	pixel.coor[2] = normal_v_cam.coor[2] * minirt->camera->focal_length
		+ U.coor[2] * x_screen + V.coor[2] * y_screen;
	if (x_screen == 0 && y_screen == 0)
	{
		printf("cam = %.2f %.2f %.2f\n", normal_v_cam.coor[0], normal_v_cam.coor[1], normal_v_cam.coor[2]);
		printf("U = %.2f %.2f %.2f\n", U.coor[0], U.coor[1], U.coor[2]);
		printf("V = %.2f %.2f %.2f\n", V.coor[0], V.coor[1], V.coor[2]);
		
	}
	return (vec_normalization2(pixel));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in,
					normal))));
}

t_ray	transform_ray(t_ray ray, t_canva matrix)
{
	t_ray	ray_transform;
	t_tuple	origin;
	t_tuple	direction;

	origin = multiplying_matrix_tuple(matrix, ray.origin);
	direction = multiplying_matrix_tuple(matrix, ray.direction);
	ray_transform.origin = origin;
	ray_transform.direction = direction;
	return (ray_transform);
}
