/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:32 by nojia             #+#    #+#             */
/*   Updated: 2025/01/14 17:31:01 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersec_sphere(t_minirt *minirt, t_ray rayon, t_shape sphere)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	
	a = (rayon.direction.coor[0] * rayon.direction.coor[0]) + (rayon.direction.coor[1] * rayon.direction.coor[1]) + (rayon.direction.coor[2] * rayon.direction.coor[2]);
	b = 2 * ((minirt->camera->xyz.coor[0] - sphere.xyz.coor[0])
		* rayon.direction.coor[0] + ((minirt->camera->xyz.coor[1]
		- sphere.xyz.coor[1]) * rayon.direction.coor[1])
		+ ((minirt->camera->xyz.coor[2] - sphere.xyz.coor[2])
		* rayon.direction.coor[2]));
	if (b > 0)
		return (-1);
	c = pow(minirt->camera->xyz.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(minirt->camera->xyz.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(minirt->camera->xyz.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		return (-b / (2 * a));
	return (get_min((-b + sqrt(delta)) / (2 * a), (-b - sqrt(delta))
		/ (2 * a))); 
} 

double	intersec_plan(t_minirt *minirt, t_tuple pixel, t_shape plan)
{
	t_tuple	p;
	t_tuple	o;

	p = create_tuple2(plan.xyz.coor[0], plan.xyz.coor[1],
		plan.xyz.coor[2], 1);
	o = create_tuple2(minirt->camera->xyz.coor[0],
		minirt->camera->xyz.coor[1],
		minirt->camera->xyz.coor[2], 1);
	if (dot_product2(plan.vector_xyz, pixel) == 0)
		return (-1);
	return ((dot_product2(plan.vector_xyz,
		vec_sub_vec2(p, o)))
		/ dot_product2(plan.vector_xyz, pixel));
}
static int	point_in_cylinder(t_shape cy, t_tuple intersec)
{
	t_tuple	intersec_proj;

	intersec_proj = vec_add_vec2(*(t_tuple *)&cy.xyz, vec_multiplication2(
		cy.vector_xyz, dot_product2(create_tuple2(
		intersec.coor[0] - cy.xyz.coor[0],
		intersec.coor[1] - cy.xyz.coor[1],
		intersec.coor[2] - cy.xyz.coor[2], 1), cy.vector_xyz)));
	if (dot_product2(create_tuple2(intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2], 1), cy.vector_xyz) < 0)
		return (0);
	if (vec_magnitude2(create_tuple2(
		intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2], 1)) > cy.height)
		return (0);
	return (1);
}

static void	get_bases_cy(t_shape cy, t_shape *base1, t_shape *base2)
{
	base1->xyz.coor[0] = cy.xyz.coor[0];
	base1->xyz.coor[1] = cy.xyz.coor[1];
	base1->xyz.coor[2] = cy.xyz.coor[2];
	base1->vector_xyz = cy.vector_xyz;
	cy.xyz = apply_vec_to_nbr(vec_multiplication2(cy.vector_xyz, cy.height), cy.xyz);
	base2->xyz.coor[0] = cy.xyz.coor[0];
	base2->xyz.coor[1] = cy.xyz.coor[1];
	base2->xyz.coor[2] = cy.xyz.coor[2];
	base2->vector_xyz = cy.vector_xyz;
}

static double	intersec_base_cy(t_minirt *minirt, t_tuple pixel, t_shape cy)
{
	t_shape	b1;
	t_shape	b2;
	t_tuple	intersec;
	double	dist_plan;
	
	get_bases_cy(cy, &b1, &b2);
	dist_plan = get_min(intersec_plan(minirt, pixel, b2), intersec_plan(minirt, pixel, b1));
	if (dist_plan < 0)
		return (-1);
	intersec = apply_vec_to_nbr(vec_multiplication2(pixel, dist_plan), cy.xyz);
	if (vec_magnitude2(vec_sub_vec2(b1.xyz, intersec)) > cy.diameter / 2)
		return (-1);
	return (dist_plan);
}

double	intersec_cylinder(t_minirt *minirt, t_tuple pixel, t_shape cy)
{
	double	quadratic[3];
	double	delta;
	t_tuple	intersec;
	t_tuple	oc;
	// t_shape	base1;
	// t_shape	base2;
	// double	b1;
	// double	b2;

	oc = vec_sub_vec2(*(t_tuple *)&minirt->camera->xyz,
		*(t_tuple *)&cy.xyz);
	pixel = vec_normalization2(pixel);
	quadratic[0] = dot_product2(pixel, pixel) - pow(dot_product2(pixel,
		vec_normalization2(cy.vector_xyz)), 2);
	quadratic[1] = 2 * (dot_product2(pixel, oc) - dot_product2(pixel, cy.vector_xyz)
		* dot_product2(oc, cy.vector_xyz));
	quadratic[2] = dot_product2(oc, oc) - pow(dot_product2(oc, cy.vector_xyz), 2) - pow(cy.diameter / 2, 2);
	delta = pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2];
	if (delta < 0)
		return (-1);
	intersec = apply_vec_to_nbr(vec_multiplication2(pixel, get_min((
		-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
		(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]))),
		minirt->camera->xyz);
	if (!point_in_cylinder(cy, intersec))
		return (intersec_base_cy(minirt, pixel, cy));
	return (get_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
		(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0])));
}