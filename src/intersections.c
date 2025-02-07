/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:32 by nojia             #+#    #+#             */
/*   Updated: 2025/02/07 16:06:02 by nadjemia         ###   ########.fr       */
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

	p = create_tuple2(plan.xyz.coor[0], plan.xyz.coor[1],
			plan.xyz.coor[2], 0);
	o = create_tuple2(source.coor[0],
			source.coor[1],
			source.coor[2], 0);
	if (dot_product2(plan.tuple_xyz, rayon.direction) == 0)
		return (-1);
	distance = (dot_product2(plan.tuple_xyz, vec_sub_vec2(p, o)))
		/ dot_product2(plan.tuple_xyz, rayon.direction);
	if (vec_magnitude2(vec_sub_vec2(plan.xyz,
				apply_vec_to_nbr(vec_multiplication2(rayon.direction,
						distance), source))) > plan.diameter / 2)
		return (-1);
	return (distance);
}

static int	point_in_cylinder(t_shape cy, t_tuple intersec)
{
	t_tuple	intersec_proj;

	intersec_proj = vec_add_vec2(cy.xyz, vec_multiplication2(
				cy.tuple_xyz, dot_product2(create_tuple2(
						intersec.coor[0] - cy.xyz.coor[0],
						intersec.coor[1] - cy.xyz.coor[1],
						intersec.coor[2] - cy.xyz.coor[2], 0), cy.tuple_xyz)));
	if (dot_product2(create_tuple2(intersec_proj.coor[0] - cy.xyz.coor[0],
				intersec_proj.coor[1] - cy.xyz.coor[1],
				intersec_proj.coor[2] - cy.xyz.coor[2], 0), cy.tuple_xyz) < 0)
		return (0);
	if (vec_magnitude2(create_tuple2(
				intersec_proj.coor[0] - cy.xyz.coor[0],
				intersec_proj.coor[1] - cy.xyz.coor[1],
				intersec_proj.coor[2] - cy.xyz.coor[2], 0)) > cy.height)
		return (0);
	return (1);
}

static void	get_bases_cy(t_shape cy, t_shape *base1, t_shape *base2)
{
	base1->xyz.coor[0] = cy.xyz.coor[0];
	base1->xyz.coor[1] = cy.xyz.coor[1];
	base1->xyz.coor[2] = cy.xyz.coor[2];
	base1->tuple_xyz = cy.tuple_xyz;
	base1->diameter = cy.diameter;
	cy.xyz = apply_vec_to_nbr(vec_multiplication2(cy.tuple_xyz,
				cy.height), cy.xyz);
	base2->xyz.coor[0] = cy.xyz.coor[0];
	base2->xyz.coor[1] = cy.xyz.coor[1];
	base2->xyz.coor[2] = cy.xyz.coor[2];
	base2->tuple_xyz = cy.tuple_xyz;
	base2->diameter = cy.diameter;
}

static double	intersec_base_cy(t_tuple source, t_ray rayon, t_shape cy)
{
	t_shape	b1;
	t_shape	b2;
	double	dist_plan;

	get_bases_cy(cy, &b1, &b2);
	dist_plan = get_positive_min(intersec_plan(source, rayon, b2),
			intersec_plan(source, rayon, b1));
	if (dist_plan < 0)
		return (-1);
	return (dist_plan);
}

int	truncate_cylinder(t_shape cy, t_ray rayon, double t0, double t1)
{
	double	minimum;
	double	maximum;
	double	point0;
	double	point1;
	int		axis_index;

	axis_index = 1;
	if (cy.tuple_xyz.coor[0] == 1)
		axis_index = 0;
	minimum = cy.xyz.coor[axis_index];
	maximum = cy.xyz.coor[axis_index] + cy.height;
	point0 = rayon.origin.coor[axis_index] + t0 * rayon.direction.coor[axis_index];
	if (minimum < point0 && point0 < maximum)
		return (1);
	point1 = rayon.origin.coor[axis_index] + t1 * rayon.direction.coor[axis_index];
	if (minimum < point1 && point1 < maximum)
		return (1);
	return (0);
}

double	intersec_cylinder(t_tuple source, t_ray rayon, t_shape cy)
{
	double	quadratic[3];
	double	delta;
	t_tuple	intersec;
	t_tuple	oc;

	delta = 0;
	cy.close = 0;
	oc = vec_sub_vec2(source,
			cy.xyz);
	rayon.direction = vec_normalization2(rayon.direction);
	quadratic[0] = dot_product2(rayon.direction, rayon.direction) - pow(
			dot_product2(rayon.direction, vec_normalization2(cy.tuple_xyz)), 2);
	quadratic[1] = 2 * (dot_product2(rayon.direction, oc) - dot_product2(
				rayon.direction, vec_normalization2(cy.tuple_xyz)) * dot_product2(oc, vec_normalization2(cy.tuple_xyz)));
	quadratic[2] = dot_product2(oc, oc) - pow(dot_product2(oc, vec_normalization2(cy.tuple_xyz)), 2)
		- pow(cy.diameter / 2, 2);
	delta = pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2];
	if (delta < 0)
		return (-1);
	if (!truncate_cylinder(cy, rayon, (-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]),\
		(-quadratic[1] + sqrt(delta)) / (2 * quadratic[0])))
		return (0);
	intersec = apply_vec_to_nbr(vec_multiplication2(rayon.direction,
				get_positive_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
					(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]))),
			source);
	if (!point_in_cylinder(cy, intersec))
	{
		cy.close = 1;
		return (intersec_base_cy(source, rayon, cy));
	}
	return (get_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
			(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0])));
}