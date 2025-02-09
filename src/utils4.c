/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:45 by nojia             #+#    #+#             */
/*   Updated: 2025/02/09 18:24:26 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	get_positive_min(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	else if (a >= 0 && b < 0)
		return (a);
	else if (b >= 0 && a < 0)
		return (b);
	else if (a < b)
		return (a);
	else
		return (b);
}

void	print_coor(void *coor)
{
	t_tuple	*vec;

	vec = (t_tuple *)coor;
	printf("%f %f %f\n", vec->coor[0], vec->coor[1], vec->coor[2]);
}

t_tuple	negate_tuple(t_tuple tuple)
{
	tuple.coor[0] = -tuple.coor[0];
	tuple.coor[1] = -tuple.coor[1];
	tuple.coor[2] = -tuple.coor[2];
	return (tuple);
}

t_tuple	normal_tuple_sphere(t_shape sphere, t_tuple world_point)
{
	t_tuple	result_world;
	t_tuple	*normalized_result_world;

	result_world = vec_sub_vec2(world_point, sphere.xyz);
	normalized_result_world = vec_normalization(&result_world);
	return (*normalized_result_world);
}

void	clean_window(t_minirt *minirt)
{
	size_t	i;
	size_t	j;
	int		pixel_offset;

	minirt->img = mlx_get_data_addr(minirt->addr_img, &minirt->bits,
			&minirt->size_line, &minirt->endian);
	if (!minirt->img)
	{
		free_minirt(minirt);
		exit(1);
	}
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixel_offset = i * minirt->size_line + j * (minirt->bits / 8);
			*(int *)(minirt->img + pixel_offset) = 0x000000;
			j++;
		}
		i++;
	}
}
