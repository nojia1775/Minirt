/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/19 19:02:35 by nojia            ###   ########.fr       */
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

t_shape	*closest_shape(t_minirt *minirt, t_vector pixel)
{
	t_shape	*tmp;
	t_shape	*shape;
	double	min;
	double	distance;
	
	shape = NULL;
	min = 1e10;
	tmp = minirt->sphere;
	while (tmp)
	{
		distance = intersec_sphere(minirt, pixel, *tmp);
		if (distance != -1 && distance < min)
		{
			shape = tmp;
			min = distance;
		}
		tmp = tmp->next;
	}
	return (shape);
}
 
void	display(t_minirt *minirt)
{
	t_vector	pixel;
	t_shape	*sphere;

	int y = 2;
	while (y < HEIGHT)
	{
		int x = 2;
		while (x < WIDTH)
		{
			sphere = NULL;
			pixel = get_pixel_vector(minirt, x, y);
			sphere = closest_shape(minirt, pixel);
			if (sphere)
				print_pixel(minirt, *sphere, x, y);
			x += 5;
		}
		y += 5;
	}
}
