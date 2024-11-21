/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:41 by nojia             #+#    #+#             */
/*   Updated: 2024/11/21 16:37:45 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	cam_around_y(t_minirt *minirt, double angle)
{
	double	x;
	double	z;

	x = minirt->camera->vector_xyz.coor[0];
	z = minirt->camera->vector_xyz.coor[2];
	minirt->camera->vector_xyz.coor[0] = x * cos(angle) + z * sin(angle);
	minirt->camera->vector_xyz.coor[2] = -x * sin(angle) + z * cos(angle);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_look_updown(t_minirt *minirt, double angle)
{
	t_vector	right;
	t_vector	up;
	t_vector	tmp_cam;

	if (minirt->camera->vector_xyz.coor[1] >= 0.9 && angle > 0)
		return ;
	else if (minirt->camera->vector_xyz.coor[1] <= -0.9 && angle < 0)
		return ;
	tmp_cam = vec_normalization2(minirt->camera->vector_xyz);
	if (double_abs(tmp_cam.coor[0]) == 1 && double_abs(tmp_cam.coor[1]) == 0
		&& double_abs(tmp_cam.coor[2]) == 0)
		up = vec_cross(tmp_cam, create_vector2(0, 0, 1));
	else
		up = vec_cross(tmp_cam, create_vector2(1, 0, 0));
	right = vec_cross(up, tmp_cam);
	print_coor(&right); 
	minirt->camera->vector_xyz = vec_add_vec2(vec_add_vec2	
		(vec_multiplication2(tmp_cam, cos(angle)), vec_multiplication2
		(vec_cross(right, tmp_cam), sin(angle))), vec_multiplication2
		(right, dot_product2(right, tmp_cam) * (1.0 - cos(angle))));
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_go_front(t_minirt *minirt)
{
	minirt->camera->xyz = apply_vec_to_nbr(vec_multiplication2(
		vec_normalization2(minirt->camera->vector_xyz), 5),
		minirt->camera->xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_go_back(t_minirt *minirt)
{
	minirt->camera->xyz = apply_vec_to_nbr(
		vec_multiplication2(
		vec_normalization2(minirt->camera->vector_xyz), -5),
		minirt->camera->xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}