/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:19:04 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/11 13:23:45 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersec_sphere(t_tuple source, t_ray rayon, t_shape sphere)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = dot_product2(rayon.direction, rayon.direction);
	b = 2 * ((source.coor[0] - sphere.xyz.coor[0])
			* rayon.direction.coor[0] + ((source.coor[1]
					- sphere.xyz.coor[1]) * rayon.direction.coor[1])
			+ ((source.coor[2] - sphere.xyz.coor[2])
				* rayon.direction.coor[2]));
	c = pow(source.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(source.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(source.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		return (-b / (2 * a));
	return (get_min((-b + sqrt(delta)) / (2 * a), (-b - sqrt(delta))
			/ (2 * a)));
}

double	intersec_plan(t_tuple source, t_ray rayon, t_shape plan)
{
	t_tuple	p;
	t_tuple	o;
	double	distance;
	t_tuple	vpoint;
	t_tuple	point;

	p = create_tuple2(plan.xyz.coor[0], plan.xyz.coor[1],
			plan.xyz.coor[2], 0);
	o = create_tuple2(source.coor[0],
			source.coor[1],
			source.coor[2], 0);
	if (dot_product2(plan.tuple_xyz, rayon.direction) == 0)
		return (-1);
	distance = (dot_product2(plan.tuple_xyz, vec_sub_vec2(p, o)))
		/ dot_product2(plan.tuple_xyz, rayon.direction);
	if (distance < 0)
		return (-1);
	vpoint = vec_multiplication2(rayon.direction, distance);
	point = apply_vec_to_nbr(vpoint, source);
	if (vec_magnitude2(vec_sub_vec2(point, plan.xyz)) > plan.diameter / 2)
		return (-1);
	return (distance);
}

t_tuple	normal_tuple_cylindre(t_shape cy, t_tuple point)
{
	double	dist;

	dist = pow(point.coor[0], 2) + pow(point.coor[2], 2);
	if (dist < (cy.diameter / 2) && point.coor[1] >= cy.height - EPSILON)
		return (create_tuple2(0, 1, 0, 0));
	else if (dist < (cy.diameter / 2) && point.coor[1] <= cy.xyz.coor[1]
		+ EPSILON)
		return (create_tuple2(0, -1, 0, 0));
	point.coor[1] = 0;
	point.coor[3] = 0;
	return (point);
}

int	check_cap(t_ray rayon, int t, int diametre)
{
	double	x;
	double	z;

	x = rayon.origin.coor[0] + t * rayon.direction.coor[0];
	z = rayon.origin.coor[2] + t * rayon.direction.coor[2];
	if (pow(x, 2) + pow(z, 2) <= (diametre / 2))
		return (1);
	else
		return (0);
}

int	intersect_caps(t_shape cy, t_ray rayon)
{
	int		axis_index;
	double	test_cap;
	double	minimum;
	double	maximum;

	axis_index = 1;
	if (cy.tuple_xyz.coor[0] == 1)
		axis_index = 0;
	minimum = cy.xyz.coor[axis_index];
	maximum = cy.xyz.coor[axis_index] + cy.height;
	test_cap = minimum - rayon.origin.coor[1];
	if (test_cap != 0)
		test_cap = test_cap / rayon.direction.coor[1];
	if (check_cap(rayon, test_cap, cy.diameter))
		return (test_cap);
	test_cap = maximum - rayon.origin.coor[1];
	if (test_cap != 0)
		test_cap = test_cap / rayon.direction.coor[1];
	if (check_cap(rayon, test_cap, cy.diameter))
		return (test_cap);
	return (-1);
}
