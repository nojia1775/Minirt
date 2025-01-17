/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:06:00 by yrio              #+#    #+#             */
/*   Updated: 2025/01/17 19:06:02 by yrio             ###   ########.fr       */
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

	if (matrix_4X4_isinvertible(sphere.transform))
		inv_transform_sphere = inverse_matrix_4X4(sphere.transform);
	else
		inv_transform_sphere = create_matrix_identity();
	rayon = transform_ray(rayon, inv_transform_sphere);
	sphere.xyz = multiplying_matrix_4X4_tuple(sphere.transform, sphere.xyz);
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
	if (!b)
		b = 0;
	if (!c)
		c = 0;
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
		intersections->count = 1;
		return (intersections);
	}
	intersections[0].t = (-b - sqrt(delta)) / (2 * a);
	intersections[1].t = (-b + sqrt(delta)) / (2 * a);
	intersections->count = 2;
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

t_ray	transform_rayon(t_ray r, t_canva m)
{
	t_ray	new_ray;
	t_tuple	origin;
	t_tuple	direction;	

	origin = multiplying_matrix_4X4_tuple(m, r.origin);
	direction = multiplying_matrix_4X4_tuple(m, r.direction);
	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}