/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:32 by nojia             #+#    #+#             */
/*   Updated: 2024/11/26 16:14:38 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersec_sphere(t_minirt *minirt, t_vector pixel, t_shape sphere)
{
	double	b;
	double	c;
	double	delta;

	b = 2 * ((minirt->camera->xyz.coor[0] - sphere.xyz.coor[0])
		* pixel.coor[0] + ((minirt->camera->xyz.coor[1]
		- sphere.xyz.coor[1]) * pixel.coor[1])
		+ ((minirt->camera->xyz.coor[2] - sphere.xyz.coor[2])
		* pixel.coor[2]));
	if (b > 0)
		return (-1);
	c = pow(minirt->camera->xyz.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(minirt->camera->xyz.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(minirt->camera->xyz.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		return (-b / 2);
	return (get_min((-b + sqrt(delta)) / 2, (-b - sqrt(delta)) / 2));
}

double	intersec_plan(t_minirt *minirt, t_vector pixel, t_shape plan)
{
	t_vector	p;
	t_vector	o;

	p = create_vector2(plan.xyz.coor[0], plan.xyz.coor[1],
		plan.xyz.coor[2]);
	o = create_vector2(minirt->camera->xyz.coor[0],
		minirt->camera->xyz.coor[1],
		minirt->camera->xyz.coor[2]);
	if (dot_product2(plan.vector_xyz, pixel) == 0)
		return (-1);
	return ((dot_product2(plan.vector_xyz,
		vec_sub_vec2(p, o)))
		/ dot_product2(plan.vector_xyz, pixel));
}

// double	intersec_cylinder(t_minirt *minirt, t_vector pixel, t_shape cy)
// {
	
// }
double	intersec_cylinder(t_minirt *minirt, t_vector pixel, t_shape cy)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_point	intersec;
	t_vector	intersec_proj;
	
	pixel = vec_normalization2(pixel);
	a = pow(vec_magnitude2(vec_sub_vec2(pixel, vec_multiplication2(
		cy.vector_xyz, dot_product2(pixel, cy.vector_xyz)))), 2);
	b = 2 * (dot_product2(vec_sub_vec2(*(t_vector *)&minirt->camera->xyz,
		*(t_vector *)&cy.xyz), vec_sub_vec2(pixel, vec_multiplication2(
		cy.vector_xyz, dot_product2(pixel, cy.vector_xyz)))));
	c = pow(vec_magnitude2(vec_sub_vec2(*(t_vector *)&minirt->camera->xyz,
		vec_sub_vec2(*(t_vector *)&cy.xyz, vec_multiplication2(
		cy.vector_xyz, dot_product2(cy.vector_xyz, vec_sub_vec2(
		*(t_vector *)&minirt->camera->xyz, *(t_vector *)&cy.xyz)))))),
		2) - pow(cy.diameter / 2, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (-1);
	intersec = apply_vec_to_nbr(vec_multiplication2(pixel, get_min(
		(-b + sqrt(delta)) / (2 * a), (-b - sqrt(delta)) / (2 * a))),
		minirt->camera->xyz);
	intersec_proj = vec_add_vec2(*(t_vector *)&cy.xyz, vec_multiplication2(
		cy.vector_xyz, dot_product2(create_vector2(
		intersec.coor[0] - cy.xyz.coor[0],
		intersec.coor[1] - cy.xyz.coor[1],
		intersec.coor[2] - cy.xyz.coor[2]), cy.vector_xyz)));
	if (dot_product2(create_vector2(intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2]), cy.vector_xyz) < 0)
		return (-1);
	if (vec_magnitude2(create_vector2(
		intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2])) > cy.height)
		return (-1);
	return (get_min((-b + sqrt(delta)) / (2 * a),
		(-b - sqrt(delta)) / (2 * a)));
}
