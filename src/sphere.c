/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:20 by yrio              #+#    #+#             */
/*   Updated: 2024/11/14 15:50:09 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_shape	create_sphere(int height)
{
	t_shape		*sphere;
	t_matrix	mat;
	int			shape;

	shape = (height * 2) + 1;
	sphere = NULL;
	sphere = malloc(sizeof(t_shape));
	mat = create_matrix(shape, shape, shape);
	sphere->mat = &mat;
	if (height % 2)
		sphere->mat->array[height][height][height] = 1;
	return (*sphere);
}
