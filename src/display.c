/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/28 10:49:01 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	print_image(t_minirt *minirt, t_shape *shape, int x, int y)
{
	int	i;
	int	j;
	int	color;
	int	pixel_offset;

	if (shape)
		color = convert_rgb(shape->rgb);
	else
		color = 0x000000;
	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits, &minirt->size_line, &minirt->endian);
	if (!minirt->img)
	{
		free_minirt(minirt);
		exit(1);
	}
	i = y - 2;
	while (i < 5 + y - 2)
	{
		j = x - 2;
		while (j < 5 + x - 2)
		{
			pixel_offset = i * minirt->size_line + j * (minirt->bits / 8);
			*(int *)(minirt->img + pixel_offset) = color;
			j++;
		}
		i++;
	}
}

static void	print_image_precision(t_minirt *minirt, t_shape *shape, int x, int y)
{
	int	color;
	int	pixel_offset;

	if (shape)
		color = convert_rgb(shape->rgb);
	else
		color = 0x000000;
	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits, &minirt->size_line, &minirt->endian);
	pixel_offset = y * minirt->size_line + x * (minirt->bits / 8);
	*(int *)(minirt->img + pixel_offset) = color;
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
			print_image(minirt, shape, x, y);
			x += 5;
		}
		y += 5;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
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
			print_image_precision(minirt, shape, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
}
