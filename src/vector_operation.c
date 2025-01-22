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

t_tuple	*vec_add_nbr(t_tuple *vec, double nbr)
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

t_tuple	*vec_add_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] + add->coor[0];
	vec->coor[1] = vec->coor[1] + add->coor[1];
	vec->coor[2] = vec->coor[2] + add->coor[2];
	return (vec);
}

t_tuple	vec_add_vec2(t_tuple vec, t_tuple add)
{
	t_tuple	result;

	result.coor[0] = vec.coor[0] + add.coor[0];
	result.coor[1] = vec.coor[1] + add.coor[1];
	result.coor[2] = vec.coor[2] + add.coor[2];
	return (result);
}

t_tuple	*vec_sub_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] - add->coor[0];
	vec->coor[1] = vec->coor[1] - add->coor[1];
	vec->coor[2] = vec->coor[2] - add->coor[2];
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
	double	total;

	if (!vec)
		return (-1);
	total = 0;
	if (vec->coor[0] != 0.0)
		total += pow(vec->coor[0], 2);
	if (vec->coor[1] != 0.0)
		total += pow(vec->coor[1], 2);
	if (vec->coor[2] != 0.0)
		total += pow(vec->coor[2], 2);
	if (total == 0)
		return (0);
	else
		return (sqrt(total));
}

double	vec_magnitude2(t_tuple vec)
{
	double	v1;
	double	v2;
	double	v3;
	double	total;

	if (!vec.coor[0] || !vec.coor[1] || !vec.coor[2])
		return (0);
	total = 0;
	v1 = pow(vec.coor[0], 2);
	if (v1 != 0)
		total += v1;
	v2 = pow(vec.coor[1], 2);
	if (v2 != 0)
		total += v2;
	v3 = pow(vec.coor[2], 2);
	if (v3 != 0)
		total += v3;
	if (total == 0)
		return (0);
	else
		return (sqrt(total));
}

double	dot_product(t_tuple *first, t_tuple *second, int length)
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
	return (a.coor[0] * b.coor[0] + a.coor[1] * b.coor[1] + a.coor[2]
		* b.coor[2]);
}

t_tuple	*vec_normalization(t_tuple *vec)
{
	double	length;

	if (!vec)
		return (NULL);
	length = vec_magnitude(vec);
	if (length == 0)
	{
		vec->coor[0] = 0.0;
		vec->coor[1] = 0.0;
		vec->coor[2] = 0.0;
	}
	else
	{
		vec->coor[0] = vec->coor[0] / length;
		vec->coor[1] = vec->coor[1] / length;
		vec->coor[2] = vec->coor[2] / length;
	}
	vec->coor[3] = 0;
	return (vec);
}

t_tuple	vec_normalization2(t_tuple vec)
{
	t_tuple	normal;
	double	length;

	length = vec_magnitude(&vec);
	if (length == 0)
	{
		normal.coor[0] = 0.0;
		normal.coor[1] = 0.0;
		normal.coor[2] = 0.0;
	}
	else
	{
		normal.coor[0] = vec.coor[0] / length;
		normal.coor[1] = vec.coor[1] / length;
		normal.coor[2] = vec.coor[2] / length;
	}
	normal.coor[3] = 0;
	return (normal);
}

t_tuple	*vec_multiplication(t_tuple *vec, double scalar)
{
	int	count;

	count = 0;
	while (count < 3)
	{
		vec->coor[count] = vec->coor[count] * scalar;
		count++;
	}
	return (vec);
}

t_tuple	vec_multiplication2(t_tuple vec, double nbr)
{
	int		count;
	t_tuple	result;

	count = 0;
	while (count < 3)
	{
		result.coor[count] = vec.coor[count] * nbr;
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
