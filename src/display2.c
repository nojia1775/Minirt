/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:18:37 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/11 13:18:48 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_shape	*closest_sphere(t_minirt *minirt, t_tuple source, t_ray rayon,
	double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;

	shape = NULL;
	tmp = minirt->sphere;
	while (tmp)
	{
		distance = intersec_sphere(source, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_plan(t_minirt *minirt, t_tuple source, t_ray rayon,
	double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;

	shape = NULL;
	tmp = minirt->plan;
	while (tmp)
	{
		distance = intersec_plan(source, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_cylinder(t_minirt *minirt, t_tuple source, t_ray rayon,
	double *min)
{
	t_shape		*tmp;
	t_shape		*shape;
	double		distance;

	shape = NULL;
	tmp = minirt->cylinder;
	while (tmp)
	{
		distance = intersec_cylinder(source, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

t_shape	*closest_shape(t_minirt *minirt, t_tuple source, t_ray rayon)
{
	double	min;
	t_shape	*shape;
	t_shape	*tmp;

	shape = NULL;
	min = 1000;
	tmp = closest_sphere(minirt, source, rayon, &min);
	if (tmp)
	{
		shape = tmp;
		shape->distance = min;
	}
	tmp = closest_plan(minirt, source, rayon, &min);
	if (tmp)
	{
		shape = tmp;
		shape->distance = min;
	}
	tmp = closest_cylinder(minirt, source, rayon, &min);
	if (tmp)
	{
		shape = tmp;
		shape->distance = min;
	}
	return (shape);
}
