/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/04 18:30:42 by nojia            ###   ########.fr       */
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

// static void	print_image_precision(t_minirt *minirt, t_shape *shape,
// 	int x, int y)
// {
// 	int		color;
// 	int		pixel_offset;
// 	t_uint8	rgb[3];

// 	rgb[0] = shape->rgb[0] * (minirt->color / 3);
// 	rgb[1] = shape->rgb[1] * (minirt->color / 3);
// 	rgb[2] = shape->rgb[2] * (minirt->color / 3);
// 	color = convert_rgb(rgb);
// 	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits,
// 			&minirt->size_line, &minirt->endian);
// 	if (!minirt->img)
// 	{
// 		free_minirt(minirt);
// 		exit(1);
// 	}
// 	pixel_offset = y * minirt->size_line + x * (minirt->bits / 8);
// 	*(int *)(minirt->img + pixel_offset) = color;
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

void	compute_pixel(t_minirt *minirt, t_ray rayon, t_shape shape,
	int *coor)
{
	t_tuple	point;
	t_tuple	normalv;

	point = vec_multiplication2(rayon.direction, shape.distance);
	if (shape.type == CYLINDER && shape.close == 1)
		normalv = normal_tuple_cylindre(shape, point);
	else
		normalv = normal_tuple_sphere(shape, point);
	minirt->color = lighting(minirt, point, negate_tuple(rayon.direction),
				normalv);
	// if (shape.type == PLAN)
	// 	minirt->color = minirt->light->luminosity * 3;
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
			shape = closest_shape(minirt, minirt->camera->xyz, rayon);
			if (shape)
				compute_pixel(minirt, rayon, *shape, coor);
			coor[0]++;
		}
		coor[1]++;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->addr_img, 0, 0);
}
