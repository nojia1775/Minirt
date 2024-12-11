/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:13:26 by yrio              #+#    #+#             */
/*   Updated: 2024/12/11 11:49:31 by yrio             ###   ########.fr       */
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

t_intersection	*point_intersection_sphere(t_ray rayon, t_shape sphere)
{
	t_intersection	*intersections;
	t_intersection	inter1;
	t_intersection	inter2;
	t_canva			inv_transform_sphere;
	double	a;
	double	b;
	double	c;
	double	delta;

	inv_transform_sphere = inverse_matrix_4X4(sphere.transform);
	rayon = transform_ray(rayon, inv_transform_sphere);
	sphere.xyz = multiplying_matrix_tuple(sphere.transform, sphere.xyz);
	inter1 = create_struct_intersection(0, sphere);
	inter2 = create_struct_intersection(0, sphere);
	intersections = aggregating_intersections(inter1, inter2);
	a = ((rayon.direction.coor[0] * rayon.direction.coor[0]) +
		(rayon.direction.coor[1] * rayon.direction.coor[1]) +
		(rayon.direction.coor[2] * rayon.direction.coor[2]));
	b = 2 * ((rayon.origin.coor[0] - sphere.xyz.coor[0])
		* rayon.direction.coor[0] + ((rayon.origin.coor[1]
		- sphere.xyz.coor[1]) * rayon.direction.coor[1])
		+ ((rayon.origin.coor[2] - sphere.xyz.coor[2])
		* rayon.direction.coor[2]));
	c = pow(rayon.origin.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(rayon.origin.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(rayon.origin.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
	{
		intersections->count = 0;
		return (intersections);
	}
	if (delta == 0)
	{
		intersections[0].t = -b / 2;
		intersections[1].t = -b / 2;
		return (intersections);
	}
	intersections[0].t = (-b - sqrt(delta)) / (2 * a);
	intersections[1].t = (-b + sqrt(delta)) / (2 * a);
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
	
	inter_agr = malloc(3 * sizeof(t_intersection));
	inter_agr[0] = i1;
	inter_agr[1] = i2;
	inter_agr[0].count = 2;
	inter_agr[1].count = 2;
	return (inter_agr);
}

t_intersection	*aggregating_4_intersections(t_intersection i1, t_intersection i2, t_intersection i3, t_intersection i4)
{
	t_intersection	*inter_agr;
	
	inter_agr = malloc(5 * sizeof(t_intersection));
	inter_agr[0] = i1;
	inter_agr[1] = i2;
	inter_agr[0].count = 4;
	inter_agr[1].count = 4;
	inter_agr[2] = i3;
	inter_agr[3] = i4;
	inter_agr[2].count = 4;
	inter_agr[3].count = 4;
	return (inter_agr);
}

t_intersection	hit(t_intersection *intersections)
{
	int	count;
	t_intersection	inter;

	count = 1;
	inter = intersections[0];
	while (count < intersections->count)
	{
		if (intersections[count].t < inter.t && intersections[count].t >= 0)
			inter = intersections[count];
		count++;
	}
	if (inter.t < 0)
		inter.count = 0;
	return (inter);
}
