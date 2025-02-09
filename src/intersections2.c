/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:36:14 by yrio              #+#    #+#             */
/*   Updated: 2025/02/09 19:48:07 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
// 
// static void	get_bases_cy(t_shape cy, t_shape *base1, t_shape *base2)
// {
// 	base1->xyz.coor[0] = cy.xyz.coor[0];
// 	base1->xyz.coor[1] = cy.xyz.coor[1];
// 	base1->xyz.coor[2] = cy.xyz.coor[2];
// 	base1->tuple_xyz = cy.tuple_xyz;
// 	base1->diameter = cy.diameter;
// 	base1->rgb[0] = cy.rgb[0];
// 	base1->rgb[1] = cy.rgb[1];
// 	base1->rgb[2] = cy.rgb[2];
// 	base1->type = PLAN;
// 	cy.xyz = apply_vec_to_nbr(vec_multiplication2(cy.tuple_xyz,
// 				cy.height), cy.xyz);
// 	base2->xyz.coor[0] = cy.xyz.coor[0];
// 	base2->xyz.coor[1] = cy.xyz.coor[1];
// 	base2->xyz.coor[2] = cy.xyz.coor[2];
// 	base2->tuple_xyz = cy.tuple_xyz;
// 	base2->diameter = cy.diameter;
// 	base2->rgb[0] = cy.rgb[0];
// 	base2->rgb[1] = cy.rgb[1];
// 	base2->rgb[2] = cy.rgb[2];
// 	base2->type = PLAN;
// }
// 
// static t_cy_part	intersec_base_cy(t_tuple source, t_ray rayon, t_shape cy)
// {
// 	t_shape		b1;
// 	t_shape		b2;
// 	double		dist_plan;
// 	t_cy_part	cy_part1;
// 	t_cy_part	cy_part2;
// 
// 	get_bases_cy(cy, &b1, &b2);
// 	cy_part1.shape = &b1;
// 	cy_part1.distance = intersec_plan(source, rayon, b1);
// 	cy_part2.shape = &b2;
// 	cy_part2.distance = intersec_plan(source, rayon, b2);
// 	dist_plan = get_positive_min(intersec_plan(source, rayon, *cy_part2.shape),
// 			intersec_plan(source, rayon, *cy_part1.shape));
// 	if (dist_plan < 0)
// 	{
// 		cy_part1.shape = NULL;
// 		cy_part1.distance = -1;
// 		return (cy_part1);
// 	}
// 	if (dist_plan == cy_part1.distance)
// 		return (cy_part1);
// 	return (cy_part2);
// }

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

t_cy_part	intersec_cylinder(t_tuple source, t_ray rayon, t_shape cy)
{
	double	quadratic[3];
	double	delta;
	t_tuple	intersec;
	t_tuple	oc;
	t_cy_part	cy_part;
	
	cy_part.shape = NULL;
	cy_part.distance = -1;
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
		return (cy_part);
	if (!truncate_cylinder(cy, rayon, (-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]),
		(-quadratic[1] + sqrt(delta)) / (2 * quadratic[0])))
		return (cy_part);
	intersec = apply_vec_to_nbr(vec_multiplication2(rayon.direction,
			get_positive_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
			(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]))),
			source);
	if (!point_in_cylinder(cy, intersec))	
	{
		cy.close = 1;
		return (cy_part);
	}
	cy_part.shape = &cy;
	cy_part.distance = get_positive_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
					(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]));
	// cy_part.shape = &cy;
	// cy_part.distance = get_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
	// 		(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]));
	return (cy_part);
}