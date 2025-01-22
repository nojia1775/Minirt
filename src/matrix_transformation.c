/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:26:00 by yrio              #+#    #+#             */
/*   Updated: 2025/01/22 16:50:10 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva	translation(double x, double y, double z)
{
	t_canva	mat;

	mat = create_canva();
	mat.array[0][0] = 1.0;
	mat.array[0][1] = 0.0;
	mat.array[0][2] = 0.0;
	mat.array[0][3] = x;
	mat.array[1][0] = 0.0;
	mat.array[1][1] = 1.0;
	mat.array[1][2] = 0.0;
	mat.array[1][3] = y;
	mat.array[2][0] = 0.0;
	mat.array[2][1] = 0.0;
	mat.array[2][2] = 1.0;
	mat.array[2][3] = z;
	mat.array[3][0] = 0.0;
	mat.array[3][1] = 0.0;
	mat.array[3][2] = 0.0;
	mat.array[3][3] = 1.0;
	return (mat);
}

t_canva	scaling(double x, double y, double z)
{
	t_canva	mat;

	mat = create_canva();
	mat.array[0][0] = x;
	mat.array[0][1] = 0.0;
	mat.array[0][2] = 0.0;
	mat.array[0][3] = 0.0;
	mat.array[1][0] = 0.0;
	mat.array[1][1] = y;
	mat.array[1][2] = 0.0;
	mat.array[1][3] = 0.0;
	mat.array[2][0] = 0.0;
	mat.array[2][1] = 0.0;
	mat.array[2][2] = z;
	mat.array[2][3] = 0.0;
	mat.array[3][0] = 0.0;
	mat.array[3][1] = 0.0;
	mat.array[3][2] = 0.0;
	mat.array[3][3] = 1.0;
	return (mat);
}

t_canva	rotation_x(double radian)
{
	t_canva	mat;

	mat = create_canva();
	mat.array[0][0] = 1.0;
	mat.array[0][1] = 0.0;
	mat.array[0][2] = 0.0;
	mat.array[0][3] = 0.0;
	mat.array[1][0] = 0.0;
	mat.array[1][1] = cos(radian);
	mat.array[1][2] = -sin(radian);
	mat.array[1][3] = 0.0;
	mat.array[2][0] = 0.0;
	mat.array[2][1] = sin(radian);
	mat.array[2][2] = cos(radian);
	mat.array[2][3] = 0.0;
	mat.array[3][0] = 0.0;
	mat.array[3][1] = 0.0;
	mat.array[3][2] = 0.0;
	mat.array[3][3] = 1.0;
	return (mat);
}

t_canva	rotation_y(double radian)
{
	t_canva	mat;

	mat = create_canva();
	mat.array[0][0] = cos(radian);
	mat.array[0][1] = 0.0;
	mat.array[0][2] = sin(radian);
	mat.array[0][3] = 0.0;
	mat.array[1][0] = 0.0;
	mat.array[1][1] = 1.0;
	mat.array[1][2] = 0.0;
	mat.array[1][3] = 0.0;
	mat.array[2][0] = -sin(radian);
	mat.array[2][1] = 0.0;
	mat.array[2][2] = cos(radian);
	mat.array[2][3] = 0.0;
	mat.array[3][0] = 0.0;
	mat.array[3][1] = 0.0;
	mat.array[3][2] = 0.0;
	mat.array[3][3] = 1.0;
	return (mat);
}

t_canva	rotation_z(double radian)
{
	t_canva	mat;

	mat = create_canva();
	mat.array[0][0] = cos(radian);
	mat.array[0][1] = -sin(radian);
	mat.array[0][2] = 0.0;
	mat.array[0][3] = 0.0;
	mat.array[1][0] = sin(radian);
	mat.array[1][1] = cos(radian);
	mat.array[1][2] = 0.0;
	mat.array[1][3] = 0.0;
	mat.array[2][0] = 0.0;
	mat.array[2][1] = 0.0;
	mat.array[2][2] = 1.0;
	mat.array[2][3] = 0.0;
	mat.array[3][0] = 0.0;
	mat.array[3][1] = 0.0;
	mat.array[3][2] = 0.0;
	mat.array[3][3] = 1.0;
	return (mat);
}
