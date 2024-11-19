/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:06:21 by yrio              #+#    #+#             */
/*   Updated: 2024/11/19 18:47:25 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vector *create_vector(double x, double y, double z)
{
	t_vector *vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
		return (NULL);
	vec->coor[0] = x;
	vec->coor[1] = y;
	vec->coor[2] = z;
	return (vec);
}

t_vector	create_vector2(double x, double y, double z)
{
	t_vector	vec;

	vec.coor[0] = x;
	vec.coor[1] = y;
	vec.coor[2] = z;
	return (vec);
}

t_vector	get_pixel_vector(t_minirt *minirt, int x, int y)
{
	t_vector	U;
	t_vector	V;
	t_vector	normal_v_cam;
	t_vector	pixel;
	double		x_screen;
	double		y_screen;
	
	normal_v_cam = vec_normalization2(minirt->camera->vector_xyz);
	U = vec_normalization2(vec_cross(create_vector2(0, 1, 0), normal_v_cam));
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
