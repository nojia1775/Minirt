/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:27:13 by yrio              #+#    #+#             */
/*   Updated: 2025/01/09 21:03:05 by nojia            ###   ########.fr       */
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

t_tuple	apply_vec_to_nbr(t_tuple vec, t_tuple point)
{
	t_tuple	result;
	
	result.coor[0] = point.coor[0] + vec.coor[0];
	result.coor[1] = point.coor[1] + vec.coor[1];
	result.coor[2] = point.coor[2] + vec.coor[2];
	return (result);
}

t_tuple *vec_add_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] + add->coor[0];
	vec->coor[1] = vec->coor[1] + add->coor[1];
	vec->coor[2] = vec->coor[2] + add->coor[2];
	vec->coor[3] = vec->coor[3] + add->coor[3];
	return (vec);
}

t_tuple vec_add_vec2(t_tuple vec, t_tuple add)
{
	t_tuple	result;

	result.coor[0] = vec.coor[0] + add.coor[0];
	result.coor[1] = vec.coor[1] + add.coor[1];
	result.coor[2] = vec.coor[2] + add.coor[2];
	return (result);
}

t_tuple *vec_sub_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] - add->coor[0];
	vec->coor[1] = vec->coor[1] - add->coor[1];
	vec->coor[2] = vec->coor[2] - add->coor[2];
	vec->coor[3] = vec->coor[3] - add->coor[3];
	return (vec);
}

t_tuple	vec_sub_vec2(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.coor[0] = a.coor[0] - b.coor[0];
	result.coor[1] = a.coor[1] - b.coor[1];
	result.coor[2] = a.coor[2] - b.coor[2];
	return (result);
}

double	vec_magnitude(t_tuple *vec)
{
	if (!vec)
		return (-1);
	return (sqrt(pow(vec->coor[0], 2) + pow(vec->coor[1], 2) + pow(vec->coor[2], 2)));
}

double	vec_magnitude2(t_tuple vec)
{
	return (sqrt(pow(vec.coor[0], 2) + pow(vec.coor[1], 2) + pow(vec.coor[2], 2)));
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

double	dot_product2(t_tuple a, t_tuple b)
{
	return (a.coor[0] * b.coor[0] + a.coor[1] * b.coor[1]
		+ a.coor[2] * b.coor[2]);
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

t_tuple	vec_normalization2(t_tuple vec)
{
	t_tuple	normal;
	double	length;

	length = vec_magnitude(&vec);
	normal.coor[0] = vec.coor[0] / length;
	normal.coor[1] = vec.coor[1] / length;
	normal.coor[2] = vec.coor[2] / length;
	normal.coor[3] = vec.coor[3];
	return (normal);
}

t_tuple *vec_multiplication(t_tuple *vec, double scalar)
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

t_tuple vec_multiplication2(t_tuple vec, double nbr)
{
	int count;
	t_tuple	result;

	count = 0;
	while (count < 3)
	{
		result.coor[count] = vec.coor[count] * nbr;
		count++;
	}
	return (result);
}

t_tuple *vec_division(t_tuple *vec, double nbr)
{
	int count;
	t_tuple	*result;

	count = 0;
	result = NULL;
	while (count < 3)
	{
		result->coor[count] = vec->coor[count] / nbr;
		count++;
	}
	return (result);
}

t_tuple	vec_cross(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.coor[0] = a.coor[1] * b.coor[2] - a.coor[2] * b.coor[1];
	result.coor[1] = a.coor[2] * b.coor[0] - a.coor[0] * b.coor[2];
	result.coor[2] = a.coor[0] * b.coor[1] - a.coor[1] * b.coor[0];
	return (result);
}

t_tuple	negate_tuple(t_tuple tuple)
{
	tuple.coor[0] = -tuple.coor[0];
	tuple.coor[1] = -tuple.coor[1];
	tuple.coor[2] = -tuple.coor[2];
	return (tuple);
}
