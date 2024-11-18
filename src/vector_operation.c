/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:27:13 by yrio              #+#    #+#             */
/*   Updated: 2024/11/18 15:50:54 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple *vec_add_nbr(t_tuple *vec, double nbr)
{
	if (!vec)
		return (NULL);
	vec->coor[0] = vec->coor[0] + nbr;
	vec->coor[1] = vec->coor[1] + nbr;
	vec->coor[2] = vec->coor[2] + nbr;
	return (vec);
}

t_point	apply_vec_to_nbr(t_vector vec, t_point point)
{
	t_point	result;
	
	result.coor[0] = point.coor[0] + vec.coor[0];
	result.coor[1] = point.coor[1] + vec.coor[1];
	result.coor[2] = point.coor[2] + vec.coor[2];
	return (result);
}

t_vector *vec_add_vec(t_vector *vec, t_vector *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] + add->coor[0];
	vec->coor[1] = vec->coor[1] + add->coor[1];
	vec->coor[2] = vec->coor[2] + add->coor[2];
	vec->coor[3] = vec->coor[3] + add->coor[3];
	return (vec);
}

t_vector vec_add_vec2(t_vector vec, t_vector add)
{
	t_vector	result;
	result.coor[0] = vec.coor[0] + add.coor[0];
	result.coor[1] = vec.coor[1] + add.coor[1];
	result.coor[2] = vec.coor[2] + add.coor[2];
	return (result);
}

t_vector *vec_sub_vec(t_vector *vec, t_vector *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] - add->coor[0];
	vec->coor[1] = vec->coor[1] - add->coor[1];
	vec->coor[2] = vec->coor[2] - add->coor[2];
	vec->coor[3] = vec->coor[3] - add->coor[3];
	return (vec);
}

double	vec_magnitude(t_tuple *vec)
{
	if (!vec)
		return (-1);
	return (sqrt(pow(vec->coor[0], 2) + pow(vec->coor[1], 2) + pow(vec->coor[2], 2)));
}

double dot_product(t_tuple *first, t_tuple *second, int length)
{
	double	result;
	int		count;

	count = 0;
	result = 0.0;
	while (count < length)
	{
		result += first->coor[count] * second->coor[count];
		count++;
	}
	return (result);
}

t_tuple *vec_normalization(t_tuple *vec)
{
	double	magnitude;

	if (!vec)
		return (NULL);
	magnitude = vec_magnitude(vec);
	vec->coor[0] = vec->coor[0] / magnitude;
	vec->coor[1] = vec->coor[1] / magnitude;
	vec->coor[2] = vec->coor[2] / magnitude;
	return (vec);
}

t_vector	vec_normalization2(t_vector vec)
{
	t_vector	normal;
	double	length;

	length = vec_magnitude(&vec);
	normal.coor[0] = vec.coor[0] / length;
	normal.coor[1] = vec.coor[1] / length;
	normal.coor[2] = vec.coor[2] / length;
	return (normal);
}

t_vector *vec_multiplication(t_vector *vec, double scalar)
{
	int count;

	count = 0;
	while (count < 3)
	{
		vec->coor[count] = vec->coor[count] * scalar;
		count++;
	}
	return (vec);
}

t_vector vec_multiplication2(t_vector vec, double nbr)
{
	int count;
	t_vector	result;

	count = 0;
	while (count < 3)
	{
		result.coor[count] = vec.coor[count] * nbr;
		count++;
	}
	return (result);
}

t_vector	vec_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.coor[0] = a.coor[1] * b.coor[2] - a.coor[2] * b.coor[1];
	result.coor[1] = a.coor[2] * b.coor[0] - a.coor[0] * b.coor[2];
	result.coor[2] = a.coor[0] * b.coor[1] - a.coor[1] * b.coor[0];
	return (result);
}
