/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:33:25 by yrio              #+#    #+#             */
/*   Updated: 2025/02/04 17:26:18 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva	multiplying_matrix(t_canva *mat1, t_canva *mat2)
{
	t_canva	result;
	int		count;
	int		count2;

	count = 0;
	result = create_canva();
	while (count < mat1->shape[0])
	{
		count2 = 0;
		while (count2 < mat2->shape[1])
		{
			result.array[count][count2] = mat1->array[count][0]
				* mat2->array[0][count2]
				+ mat1->array[count][1] * mat2->array[1][count2]
				+ mat1->array[count][2] * mat2->array[2][count2]
				+ mat1->array[count][3] * mat2->array[3][count2];
			count2++;
		}
		count++;
	}
	return (result);
}

t_tuple	multiplying_matrix_tuple(t_canva mat, t_tuple tup)
{
	t_tuple	result;
	int		count;

	count = 0;
	result = create_tuple2(0, 0, 0, 0);
	while (count < 4)
	{
		result.coor[count] = mat.array[count][0] * tup.coor[0]
			+ mat.array[count][1] * tup.coor[1]
			+ mat.array[count][2] * tup.coor[2]
			+ mat.array[count][3] * tup.coor[3];
		count++;
	}
	return (result);
}
