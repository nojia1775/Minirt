/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:41 by nojia             #+#    #+#             */
/*   Updated: 2024/11/26 16:22:42 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	cam_look_leftright(t_minirt *minirt, double angle)
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
	t_vector	old_cam;
	t_vector	up;

	if ((minirt->camera->vector_xyz.coor[1] >= 0.9 && angle < 0)
		|| (minirt->camera->vector_xyz.coor[1] <= -0.9 && angle > 0))
		return ;
	old_cam = vec_normalization2(minirt->camera->vector_xyz);
	if (double_abs(old_cam.coor[0]) == 0 && double_abs(old_cam.coor[1]) == 1
		&& double_abs(old_cam.coor[2]) == 0)
		up = create_vector2(-1, 0, 0);
	else
		up = create_vector2(0, 1, 0);
	up = vec_cross(vec_cross(up, old_cam), old_cam);
	up = vec_normalization2(up);
	minirt->camera->vector_xyz.coor[0] = old_cam.coor[0] * cos(angle)
		+ up.coor[0] * sin(angle);
	minirt->camera->vector_xyz.coor[1] = old_cam.coor[1] * cos(angle)
		+ up.coor[1] * sin(angle);
	minirt->camera->vector_xyz.coor[2] = old_cam.coor[2] * cos(angle)
		+ up.coor[2] * sin(angle);
	minirt->camera->vector_xyz = vec_normalization2(minirt->camera->vector_xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_go_frontback(t_minirt *minirt, int dir)
{
	minirt->camera->xyz = apply_vec_to_nbr(vec_multiplication2(
		vec_normalization2(minirt->camera->vector_xyz), 5 * dir),
		minirt->camera->xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_go_leftright(t_minirt *minirt, int left_right)
{
	t_vector	right;
	t_vector	up;

	if (double_abs(minirt->camera->vector_xyz.coor[0] == 0
		&& double_abs(minirt->camera->vector_xyz.coor[1] == 1
		&& double_abs(minirt->camera->vector_xyz.coor[2] == 0))))
		up = create_vector2(-1, 0, 0);
	else
		up = create_vector2(0, -1, 0);
	up = vec_cross(vec_cross(up, minirt->camera->vector_xyz),
		minirt->camera->vector_xyz);
	right = vec_cross(up, minirt->camera->vector_xyz);
	right = vec_multiplication2(right, left_right * 5);
	minirt->camera->xyz = apply_vec_to_nbr(right, minirt->camera->xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}

void	cam_go_updown(t_minirt *minirt, int up_down)
{
	t_vector	up;

	up.coor[0] = 0;
	up.coor[1] = 5;
	up.coor[2] = 0;
	minirt->camera->xyz = apply_vec_to_nbr(vec_multiplication2(up, up_down),
		minirt->camera->xyz);
	mlx_clear_window(minirt->mlx, minirt->win);
	display(minirt);
}
