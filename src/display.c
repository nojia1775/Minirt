/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2025/01/14 11:01:58 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// static void	print_image(t_minirt *minirt, t_shape *shape, int x, int y, double shading)
// {
// 	int	i;
// 	int	j;
// 	int	pixel_offset;
// 	// t_uint8	rgb[3];
// 	int	color;
// 
// 	if (shape)
// 	{
// 		color = shading;
// 		// rgb[0] = shape->rgb[0] * (shading / 3);
// 		// rgb[1] = shape->rgb[1] * (shading / 3);
// 		// rgb[2] = shape->rgb[2] * (shading / 3);
// 		// color = convert_rgb(rgb);
// 	}
// 	else
// 		color = 0x000000;
// 	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits, &minirt->size_line, &minirt->endian);
// 	if (!minirt->img)
// 	{
// 		free_minirt(minirt);
// 		exit(1);
// 	}
// 	i = y - 2;
// 	while (i < 5 + y - 2)
// 	{
// 		j = x - 2;
// 		while (j < 5 + x - 2)
// 		{
// 			pixel_offset = i * minirt->size_line + j * (minirt->bits / 8);
// 			*(int *)(minirt->img + pixel_offset) = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }

static void	print_image_precision(t_minirt *minirt, t_shape *shape, int x, int y, double shading)
{
	int	color;
	int	pixel_offset;
	t_uint8	rgb[3];

	if (shape)
	{
		rgb[0] = shape->rgb[0] * (shading / 3);
		rgb[1] = shape->rgb[1] * (shading / 3);
		rgb[2] = shape->rgb[2] * (shading / 3);
		color = convert_rgb(rgb);
	}
	else
		color = 0x000000;
	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits, &minirt->size_line, &minirt->endian);
	if (!minirt->img)
	{
		free_minirt(minirt);
		exit(1);
	}
	pixel_offset = y * minirt->size_line + x * (minirt->bits / 8);
	*(int *)(minirt->img + pixel_offset) = color;
}

static t_shape	*closest_sphere(t_minirt *minirt, t_ray rayon, double *min)
{
	t_shape	*tmp;
	t_shape	*shape;
	t_intersection	*xs;
	
	shape = NULL;
	tmp = minirt->sphere;
	while (tmp)
	{
		xs = point_intersection_sphere(rayon, *tmp);
		if (xs->count > 0)
		{
			if (get_min(xs[0].t, xs[1].t) < *min)
			{
				shape = tmp;
				*min = get_min(xs[0].t, xs[1].t); 
			}
		}
		tmp = tmp->next;
	}
	if (shape)
		shape->distance = *min;
	return (shape);
}

// static t_shape	*closest_plan(t_minirt *minirt, t_tuple pixel, double *min)
// {
// 	t_shape	*tmp;
// 	t_shape	*shape;
// 	double	distance;
// 	
// 	shape = NULL;
// 	tmp = minirt->plan;
// 	while (tmp)
// 	{
// 		distance = intersec_plan(minirt, pixel, *tmp);
// 		if (distance > 0 && distance < *min)
// 		{
// 			shape = tmp;
// 			*min = distance;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (shape)
// 		shape->distance = *min;
// 	return (shape);
// }

// static t_shape	*closest_cylinder(t_minirt *minirt, t_tuple pixel, double *min)
// {
// 	t_shape	*tmp;
// 	t_shape	*shape;
// 	double	distance;
// 	
// 	shape = NULL;
// 	tmp = minirt->cylinder;
// 	while (tmp)
// 	{
// 		distance = intersec_cylinder(minirt, pixel, *tmp);
// 		if (distance > 0 && distance < *min)
// 		{
// 			shape = tmp;
// 			*min = distance;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (shape)
// 		shape->distance = *min;
// 	return (shape);
// }

// t_shape	*closest_shape(t_minirt *minirt, t_tuple pixel)
// {
// 	double	min;
// 	t_shape	*shape;
// 	t_shape	*tmp;
// 
// 	shape = NULL;
// 	min = 1000;
// 	tmp = closest_sphere(minirt, pixel, &min);
// 	if (tmp)
// 		shape = tmp;
// 	tmp = closest_plan(minirt, pixel, &min);
// 	if (tmp)
// 		shape = tmp;
// 	tmp = closest_cylinder(minirt, pixel, &min);
// 	if (tmp)
// 	{
// 		shape = tmp;
// 		shape->distance = min;
// 	}
// 	return (shape);
// }

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
		shape = tmp;
		shape->distance = min;
	}
	// tmp = closest_plan(minirt, pixel, &min);
	// if (tmp)
	// 	shape = tmp;
	// tmp = closest_cylinder(minirt, pixel, &min);
	return (shape);
}
 
// void	display(t_minirt *minirt)
// {
// 	t_tuple	pixel;
// 	t_shape	*shape;
// 	// t_tuple	intersec;
// 	// double	color;
// 
// 	// color = 0;
// 	int y = 2;
// 	while (y < HEIGHT)
// 	{
// 		int x = 2;
// 		while (x < WIDTH)
// 		{
// 			shape = NULL;
// 			pixel = get_pixel_vector(minirt, x, y);
// 			shape = closest_shape(minirt, pixel);
// 			if (shape)
// 			{
// 				// intersec = vec_multiplication2(pixel, shape->distance);
// 				//color = lighting(minirt, intersec, negate_tuple(pixel), shape);
// 			}
// 			print_image(minirt, shape, x, y, 3);
// 			x += 5;
// 		}
// 		y += 5;
// 	}
// 	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
// }

// void	display_precision(t_minirt *minirt)
// {
// 	t_tuple	pixel;
// 	t_shape	*shape;
// 	//t_ray	rayon;
// 	//double	color;
// 
// 	int y = 0;
// 	while (y < HEIGHT)
// 	{
// 		int x = 0;
// 		while (x < WIDTH)
// 		{
// 			shape = NULL;
// 			pixel = get_pixel_vector(minirt, x, y);
// 			shape = closest_shape(minirt, pixel);
// 			if (shape)
// 			{
// 				//rayon.origin = minirt->camera->xyz;
// 				//rayon.direction = pixel;
// 				//t_tuple	point = position_ray(rayon, shape->distance);
// 				//t_tuple normalv = normal_vector_sphere(*shape, point);
// 				//color = lighting(*minirt->light, point, negate_tuple(pixel), normalv);
// 			}
// 			print_image_precision(minirt, shape, x, y, 3);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
// }

void	display_manual(t_minirt	*minirt)
{
	t_ray	rayon;
	t_shape	*shape;
	double 	color;
	
	color = 3;
	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			rayon.origin = minirt->camera->xyz;
			rayon.direction = get_pixel_vector(minirt, x, y);
			shape = closest_shape(minirt, rayon);
			// if (!shape)
			// 	printf(" ");
			// else
			// 	printf("%d", shape->rgb[0] / 100);
			//if (x == 0 && y == 46)
			//	printf("%f %f %f\n", rayon.direction.coor[0], rayon.direction.coor[1], rayon.direction.coor[2]);
			if (shape)
			{
				t_intersection *xs = point_intersection_sphere(rayon, *shape);
				t_intersection intersection = hit(xs);
				t_tuple point = position_ray(rayon, intersection.t);
				t_tuple normalv = normal_vector_sphere(*shape, point);
				color = lighting(*minirt->light, point, negate_tuple(rayon.direction), normalv);
				print_image_precision(minirt, shape, x, y, color);
			}
			x++;
		}
		// printf("\n");
		y++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
}
