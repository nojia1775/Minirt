/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:06:21 by yrio              #+#    #+#             */
/*   Updated: 2024/11/14 17:07:05 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple *create_tuple(double x, double y, double z, int w)
{
	t_tuple *vec;

	vec = malloc(sizeof(t_tuple));
	if (!vec)
		return (NULL);
	vec->coor[0] = x;
	vec->coor[1] = y;
	vec->coor[2] = z;
	vec->coor[3] = w;
	return (vec);
}
