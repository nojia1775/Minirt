/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:27:13 by yrio              #+#    #+#             */
/*   Updated: 2024/11/12 16:14:02 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vector *vec_add_nbr(t_vector *vec, double nbr)
{
	if (!vec)
		return (NULL);
	vec->coor[0] = vec->coor[0] + nbr;
	vec->coor[1] = vec->coor[1] + nbr;
	vec->coor[2] = vec->coor[2] + nbr;
	return (vec);
}

t_vector *vec_add_vec(t_vector *vec, t_vector *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] + add->coor[0];
	vec->coor[1] = vec->coor[1] + add->coor[1];
	vec->coor[2] = vec->coor[2] + add->coor[2];
	return (vec);
}

t_vector *vec_sub_vec(t_vector *vec, t_vector *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] - add->coor[0];
	vec->coor[1] = vec->coor[1] - add->coor[1];
	vec->coor[2] = vec->coor[2] - add->coor[2];
	return (vec);
}

double	vec_magnitude(t_vector *vec)
{
	if (!vec)
		return (-1);
	return (sqrt(pow(vec->coor[0], 2) + pow(vec->coor[1], 2) + pow(vec->coor[1], 2)));
}

double dot_product(t_vector *first, t_vector *second, int length)
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

t_vector *vec_normalization(t_vector *vec)
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
