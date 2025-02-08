/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:38:15 by yrio              #+#    #+#             */
/*   Updated: 2025/02/08 21:41:37 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	compute_specular(t_tuple lightv, t_tuple normalv, t_tuple eyev)
{
	double	reflect_dot_eye;
	double	factor;
	t_tuple	reflectv;

	reflectv = reflect(negate_tuple(lightv), normalv);
	reflect_dot_eye = dot_product2(reflectv, eyev);
	if (reflect_dot_eye <= 0)
		return (0.0);
	else
	{
		factor = pow(reflect_dot_eye, 200.0);
		return (0.9 * factor);
	}
}

static t_shadow	compute_shadow(t_minirt *minirt, t_tuple point)
{
	t_ray	light_to_point;
	t_ray	cam_to_point;
	t_shadow	shapes;

	light_to_point.origin = minirt->light->xyz;
	light_to_point.direction = vec_normalization2(
			vec_sub_vec2(point, minirt->light->xyz));
	shapes.shape1 = closest_shape(minirt, light_to_point.origin, light_to_point);
	cam_to_point.origin = minirt->camera->xyz;
	cam_to_point.direction = vec_normalization2(
			vec_sub_vec2(point, minirt->camera->xyz));
	shapes.shape2 = closest_shape(minirt, cam_to_point.origin, cam_to_point);
	return (shapes);
}

double	lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	double	components[3];
	double	light_dot_normal;
	t_tuple	lightv;
	t_shadow	shapes;

	components[AMBIENT] = minirt->ambient->ambient;
	components[DIFFUSE] = 0.9;
	lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
	components[AMBIENT] = minirt->light->luminosity * components[AMBIENT];
	light_dot_normal = dot_product2(lightv, normalv);
	shapes = compute_shadow(minirt, point);
	if (light_dot_normal < 0 || shapes.shape1 != shapes.shape2)
	{
		components[DIFFUSE] = 0;
		components[SPECULAR] = 0;
	}
	else
	{
		components[DIFFUSE] = minirt->light->luminosity * components[DIFFUSE] * light_dot_normal;
		components[SPECULAR] = compute_specular(lightv, normalv, eyev);
	}
	return (components[AMBIENT] + components[DIFFUSE] + components[SPECULAR]);
}
