/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:35:24 by yrio              #+#    #+#             */
/*   Updated: 2025/01/30 15:59:24 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_shape	*closest_sphere(t_minirt *minirt, t_ray rayon, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;

	shape = NULL;
	tmp = minirt->sphere;
	while (tmp)
	{
		distance = intersec_sphere(minirt, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_plan(t_minirt *minirt, t_ray rayon, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;

	shape = NULL;
	tmp = minirt->plan;
	while (tmp)
	{
		distance = intersec_plan(minirt, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_cylinder(t_minirt *minirt, t_ray rayon, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;

	shape = NULL;
	tmp = minirt->cylinder;
	while (tmp)
	{
		distance = intersec_cylinder(minirt, rayon, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

t_shape	*closest_shape(t_minirt *minirt, t_ray rayon)
{
	double	min;
	t_shape	*shape;
	t_shape	*tmp;

	shape = NULL;
	min = 1000;
	tmp = closest_sphere(minirt, rayon, &min);
	if (tmp)
	{
		if (rayon.direction.coor[0] >= -0.1 && rayon.direction.coor[0] <= 0.1 && rayon.direction.coor[1] >= -1.0 && rayon.direction.coor[1] <= -0.8 && rayon.direction.coor[2] >= -0.5 && rayon.direction.coor[2] <= -0.3)
			printf("ICI\n");
		shape = tmp;
		shape->distance = min;
	}
	tmp = closest_plan(minirt, rayon, &min);
	if (tmp)
	{
		shape = tmp;
		shape->distance = min;
	}
	tmp = closest_cylinder(minirt, rayon, &min);
	if (tmp)
	{
		shape = tmp;
		shape->distance = min;
	}
	return (shape);
}
