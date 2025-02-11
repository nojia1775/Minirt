/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:36:14 by yrio              #+#    #+#             */
/*   Updated: 2025/02/09 20:12:01 by nojia            ###   ########.fr       */
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
	point0 = rayon.origin.coor[axis_index]
		+ t0 * rayon.direction.coor[axis_index];
	if (minimum < point0 && point0 < maximum)
		return (1);
	point1 = rayon.origin.coor[axis_index]
		+ t1 * rayon.direction.coor[axis_index];
	if (minimum < point1 && point1 < maximum)
		return (1);
	return (0);
}

static double	check_intersec(t_tuple source, t_ray rayon, t_shape cy,
	double quadratic[3])
{
	double	delta;
	t_tuple	intersec;

	delta = pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2];
	if (delta < 0)
		return (-1);
	if (!truncate_cylinder(cy, rayon, (-quadratic[1] - sqrt(delta))
			/ (2 * quadratic[0]), (-quadratic[1] + sqrt(delta))
			/ (2 * quadratic[0])))
		return (-1);
	intersec = apply_vec_to_nbr(vec_multiplication2(rayon.direction,
				get_positive_min((-quadratic[1] + sqrt(delta))
					/ (2 * quadratic[0]),
					(-quadratic[1] - sqrt(delta))
					/ (2 * quadratic[0]))), source);
	if (!point_in_cylinder(cy, intersec))
		return (-1);
	return (get_positive_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
			(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0])));
}

double	intersec_cylinder(t_tuple source, t_ray rayon, t_shape cy)
{
	double	quadratic[3];
	t_tuple	oc;

	cy.close = 0;
	oc = vec_sub_vec2(source,
			cy.xyz);
	rayon.direction = vec_normalization2(rayon.direction);
	quadratic[0] = dot_product2(rayon.direction, rayon.direction) - pow(
			dot_product2(rayon.direction, vec_normalization2(cy.tuple_xyz)), 2);
	quadratic[1] = 2 * (dot_product2(rayon.direction, oc) - dot_product2(
				rayon.direction, vec_normalization2(cy.tuple_xyz))
			* dot_product2(oc, vec_normalization2(cy.tuple_xyz)));
	quadratic[2] = dot_product2(oc, oc) - pow(dot_product2(oc,
				vec_normalization2(cy.tuple_xyz)), 2)
		- pow(cy.diameter / 2, 2);
	return (check_intersec(source, rayon, cy, quadratic));
}
