/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2025/01/28 14:14:17 by nadjemia         ###   ########.fr       */
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

static void	print_image_precision(t_minirt *minirt, t_shape *shape,
	int x, int y)
{
	int		color;
	int		pixel_offset;
	t_uint8	rgb[3];

	rgb[0] = shape->rgb[0] * (minirt->color / 3);
	rgb[1] = shape->rgb[1] * (minirt->color / 3);
	rgb[2] = shape->rgb[2] * (minirt->color / 3);
	color = convert_rgb(rgb);
	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits,
			&minirt->size_line, &minirt->endian);
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

// void	display(t_minirt *minirt)
// {
// 	t_ray	rayon;
// 	t_shape	*shape;
// 	t_tuple	pixel;
// 	int		y;
// 	int		x;

// 	y = 2;
// 	while (y < HEIGHT)
// 	{
// 		x = 2;
// 		while (x < WIDTH)
// 		{
// 			pixel = create_tuple2(0.0, 0.0, 0.0, 0);
// 			rayon.origin = minirt->camera->xyz;
// 			rayon.direction = get_pixel_tuple(minirt, pixel, x, y);
// 			shape = closest_shape(minirt, rayon);
// 			print_image(minirt, shape, x, y);
// 			x += 5;
// 		}
// 		y += 5;
// 	}
// 	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
// }

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

double	lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	light_dot_normal;
	t_tuple	lightv;

	ambient = 0.2;
	diffuse = 0.9;
	lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
	ambient = minirt->light->luminosity * ambient;
	light_dot_normal = dot_product2(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = 0;
		specular = 0;
	}
	else
	{
		diffuse = minirt->light->luminosity * diffuse * light_dot_normal;
		specular = compute_specular(lightv, normalv, eyev);
	}
	return (ambient + diffuse + specular);
}

void	compute_pixel(t_minirt *minirt, t_ray rayon, t_shape shape,
	int *coor)
{
	t_tuple	point;
	t_tuple	normalv;

	point = vec_multiplication2(rayon.direction, shape.distance);
	normalv = normal_tuple_sphere(shape, point);
	minirt->color = lighting(minirt, point, negate_tuple(rayon.direction),
			normalv);
	print_image_precision(minirt, &shape, coor[0], coor[1]);
}

void	display_precision(t_minirt *minirt)
{
	t_ray	rayon;
	t_shape	*shape;
	t_tuple	pixel;
	int		coor[2];

	coor[1] = 0;
	while (coor[1] < HEIGHT)
	{
		coor[0] = 0;
		while (coor[0] < WIDTH)
		{
			pixel = create_tuple2(0.0, 0.0, 0.0, 0);
			rayon.origin = minirt->camera->xyz;
			rayon.direction = get_pixel_tuple(minirt, pixel, coor[0], coor[1]);
			shape = closest_shape(minirt, rayon);
			if (shape)
				compute_pixel(minirt, rayon, *shape, coor);
			coor[0]++;
		}
		coor[1]++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
}	
