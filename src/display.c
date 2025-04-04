/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:18:56 by nadjemia          #+#    #+#             */
/*   Updated: 2025/04/04 19:14:50 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	compute_ambient(t_uint8 *color, t_uint8 *mix)
{
	color[0] = color[0] * (1 - 0.5) + mix[0] * 0.5;
	color[1] = color[1] * (1 - 0.5) + mix[1] * 0.5;
	color[2] = color[2] * (1 - 0.5) + mix[2] * 0.5;
}

static void	print_image_precision(t_minirt *minirt, t_shape *shape,
	int x, int y)
{
	int		color;
	int		pixel_offset;
	t_uint8	rgb[3];

	compute_ambient(&shape->rgb[0], minirt->ambient->rgb);
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

void	compute_pixel(t_minirt *minirt, t_ray rayon, t_shape shape,
	int *coor)
{
	t_tuple	point;
	t_tuple	normalv;
	t_tuple	vpoint;

	vpoint = vec_multiplication2(rayon.direction, shape.distance);
	point = apply_vec_to_nbr(vpoint, minirt->camera->xyz);
	if (shape.type == CYLINDER && shape.close == 1)
		normalv = normal_tuple_cylindre(shape, point);
	else
		normalv = normal_tuple_sphere(shape, point);
	if (shape.mirror)
	{
		t_ray reflect_ray = {
			.origin = point,
			.direction = (negate_tuple(rayon.direction), normalv)
		};
		t_shape *reflect_shape = closest_shape(minirt, reflect_ray.origin, reflect_ray);
		if (reflect_shape)
			compute_pixel(minirt, reflect_ray, *reflect_shape, coor);
		return;
	}
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
	minirt->sphere->mirror = 1;
	minirt->sphere->next->mirror = 1;
	while (coor[1] < HEIGHT)
	{
		coor[0] = 0;
		while (coor[0] < WIDTH)
		{
			pixel = create_tuple2(0.0, 0.0, 0.0, 0);
			rayon.origin = minirt->camera->xyz;
			rayon.direction = get_pixel_tuple(minirt, pixel, coor[0], coor[1]);
			shape = closest_shape(minirt, minirt->camera->xyz, rayon);
			if (shape)
				compute_pixel(minirt, rayon, *shape, coor);
			coor[0]++;
		}
		coor[1]++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
}
