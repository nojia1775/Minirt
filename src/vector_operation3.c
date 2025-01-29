/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:32:36 by yrio              #+#    #+#             */
/*   Updated: 2025/01/23 15:33:15 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
