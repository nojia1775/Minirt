/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:57 by yrio              #+#    #+#             */
/*   Updated: 2025/02/09 18:53:08 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
