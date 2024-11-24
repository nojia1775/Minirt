/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/24 18:06:43 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	print_pixel(t_minirt *minirt, t_shape shape, int x, int y)
{
	int	i;
	int	j;

	i = y - 2;
	while (i < 5 + y - 2)
	{
		j = x - 2;
		while (j < 5 + x - 2)
		{
			mlx_pixel_put(minirt->mlx, minirt->win, j, i, convert_rgb(shape.rgb));
			j++;
		}
		i++;
	}
}

static t_shape	*closest_sphere(t_minirt *minirt, t_vector pixel, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;
	
	shape = NULL;
	tmp = minirt->sphere;
	while (tmp)
	{
		distance = intersec_sphere(minirt, pixel, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_plan(t_minirt *minirt, t_vector pixel, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;
	
	shape = NULL;
	tmp = minirt->plan;
	while (tmp)
	{
		distance = intersec_plan(minirt, pixel, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

static t_shape	*closest_cylinder(t_minirt *minirt, t_vector pixel, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	distance;
	
	shape = NULL;
	tmp = minirt->cylinder;
	while (tmp)
	{
		distance = intersec_cylinder(minirt, pixel, *tmp);
		if (distance > 0 && distance < *min)
		{
			shape = tmp;
			*min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}

t_shape	*closest_shape(t_minirt *minirt, t_vector pixel)
{
	double	min;
	t_shape	*shape;
	t_shape	*tmp;

	shape = NULL;
	min = 1000;
	tmp = closest_sphere(minirt, pixel, &min);
	if (tmp)
		shape = tmp;
	tmp = closest_plan(minirt, pixel, &min);
	if (tmp)
		shape = tmp;
	tmp = closest_cylinder(minirt, pixel, &min);
	if (tmp)
		shape = tmp;
	return (shape);
}
 
void	display(t_minirt *minirt)
{
	t_vector	pixel;
	t_shape	*shape;

	int y = 2;
	while (y < HEIGHT)
	{
		int x = 2;
		while (x < WIDTH)
		{
			shape = NULL;
			pixel = get_pixel_vector(minirt, x, y);
			shape = closest_shape(minirt, pixel);
			if (shape)
				print_pixel(minirt, *shape, x, y);
			x += 5;
		}
		y += 5;
	}
}

void	display_precision(t_minirt *minirt)
{
	t_vector	pixel;
	t_shape	*shape;

	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			shape = NULL;
			pixel = get_pixel_vector(minirt, x, y);
			shape = closest_shape(minirt, pixel);
			if (shape)
				mlx_pixel_put(minirt->mlx, minirt->win, x, y, convert_rgb(shape->rgb));
			x++;
		}
		y++;
	}
}
