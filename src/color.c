/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:38:15 by yrio              #+#    #+#             */
/*   Updated: 2025/02/06 18:08:43 by nojia            ###   ########.fr       */
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

static void	compute_shadow(t_minirt *minirt, t_tuple point)
{
	t_ray	light_to_point;
	t_shape	*shape_between;
	t_ray	cam_to_point;
	t_shape	*shape;
}

double	lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	double	components[3];
	double	light_dot_normal;
	t_tuple	lightv;
	t_shape	*shape;
	t_ray	compute_shadow;
	t_ray	cam_ray;
	t_shape	*point_shape;

	components[AMBIENT] = minirt->ambient->ambient;
	components[DIFFUSE] = 0.9;
	lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
	components[AMBIENT] = minirt->light->luminosity * components[AMBIENT];
	light_dot_normal = dot_product2(lightv, normalv);
	compute_shadow.origin = minirt->light->xyz;
	compute_shadow.direction = vec_normalization2(
			vec_sub_vec2(point, minirt->light->xyz));
	shape = closest_shape(minirt, minirt->light->xyz, compute_shadow);
	cam_ray.direction = vec_sub_vec2(point, minirt->camera->xyz);
	cam_ray.origin = minirt->camera->xyz;
	point_shape = closest_shape(minirt, minirt->camera->xyz, cam_ray);
	if (light_dot_normal < 0 || shape != point_shape)
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
