/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:03:20 by yrio              #+#    #+#             */
/*   Updated: 2024/11/13 17:41:49 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_shape	*create_sphere(int height)
{
	t_shape	*sphere;
	int		shape;

	shape = (height * 2) + 1;
	sphere = malloc(sizeof(t_matrix));
	create_matrix(shape, shape, shape);
}