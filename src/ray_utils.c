/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:13:26 by yrio              #+#    #+#             */
/*   Updated: 2024/12/09 20:00:39 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minirt.h"

t_tuple	position_ray(t_ray rayon, double t)
{
	t_tuple	point;

	point.coor[0] = rayon.origin.coor[0] + (rayon.direction.coor[0] * t);
	point.coor[1] = rayon.origin.coor[1] + (rayon.direction.coor[1] * t);
	point.coor[2] = rayon.origin.coor[2] + (rayon.direction.coor[2] * t);
	return (point);
}

t_intersection	*point_intersection_sphere(t_tuple origin_cam, t_tuple pixel, t_shape sphere)
{
	t_intersection	*intersections;
	t_intersection	inter1;
	t_intersection	inter2;
	double	b;
	double	c;
	double	delta;

	inter1 = create_struct_intersection(0, sphere);
	inter2 = create_struct_intersection(0, sphere);
	intersections = aggregating_intersections(inter1, inter2);
	b = 2 * ((origin_cam.coor[0] - sphere.xyz.coor[0])
		* pixel.coor[0] + ((origin_cam.coor[1]
		- sphere.xyz.coor[1]) * pixel.coor[1])
		+ ((origin_cam.coor[2] - sphere.xyz.coor[2])
		* pixel.coor[2]));
	c = pow(origin_cam.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(origin_cam.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(origin_cam.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * 1 * c;
	if (delta < 0)
		return (intersections);
	if (delta == 0)
	{
		intersections[0].t = -b / 2;
		intersections[1].t = -b / 2;
		return (intersections);
	}
	intersections[0].t = (-b - sqrt(delta)) / 2;
	intersections[1].t = (-b + sqrt(delta)) / 2;
	return (intersections);
}

t_intersection	create_struct_intersection(double t, t_shape shape)
{
	t_intersection inter;
	inter.t = t;
	inter.shape = shape;
	return (inter);
}

t_intersection	*aggregating_intersections(t_intersection i1, t_intersection i2)
{
	t_intersection	*inter_agr;
	
	inter_agr = malloc(2 * sizeof(t_intersection));
	inter_agr[0] = i1;
	inter_agr[1] = i2;
	inter_agr[0].count = 2;
	inter_agr[1].count = 2;
	return (inter_agr);
}