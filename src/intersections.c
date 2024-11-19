/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:32 by nojia             #+#    #+#             */
/*   Updated: 2024/11/19 18:52:37 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersec_sphere(t_minirt *minirt, t_vector pixel, t_shape sphere)
{
	double	b;
	double	c;
	double	delta;

	b = 2 * ((minirt->camera->xyz.coor[0] - sphere.xyz.coor[0])
		* pixel.coor[0] + ((minirt->camera->xyz.coor[1]
		- sphere.xyz.coor[1]) * pixel.coor[1])
		+ ((minirt->camera->xyz.coor[2] - sphere.xyz.coor[2])
		* pixel.coor[2]));
	if (b > 0)
		return (-1);
	c = pow(minirt->camera->xyz.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(minirt->camera->xyz.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(minirt->camera->xyz.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		return (-b / 2);
	return (get_min((-b + sqrt(delta)) / 2, (-b - sqrt(delta)) / 2));
}
