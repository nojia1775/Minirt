/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:33:25 by yrio              #+#    #+#             */
/*   Updated: 2024/11/19 17:33:56 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva    multiplying_4X4_matrix(t_canva *mat1, t_canva *mat2)
{
	t_canva result;
	int     count;
	int     count2;	
	count = 0;
	result = create_canva(4, 4);
	while (count < mat1->shape[0])
	{
		count2 = 0;
		while (count2 < mat2->shape[1])
		{
			result.array[count][count2] = mat1->array[count][0] * mat2->array[0][count2] +
			mat1->array[count][1] * mat2->array[1][count2] +
			mat1->array[count][2] * mat2->array[2][count2] +
			mat1->array[count][3] * mat2->array[3][count2];
			count2++;
		}
		count++;
	}
	return (result);
}

t_tuple multiplying_matrix_tuple(t_canva mat, t_tuple tup)
{
	t_tuple *result;
	int count;
	count = 0;
	result = create_tuple(0, 0, 0, 0);
	while (count < mat.shape[0])
	{
		result->coor[count] = mat.array[count][0] * tup.coor[0] +
	        mat.array[count][1] * tup.coor[1] +
	        mat.array[count][2] * tup.coor[2] +
	        mat.array[count][3] * tup.coor[3];
		count++;
	}
	return (*result);
}

t_canva transpose_4X4_matrix(t_canva mat)
{
	t_canva result;
	int     count;
	int     count2;

	result = create_canva(4, 4);
	count = 0;
	count2 = 0;
	while (count < 4)
	{
		count2 = 0;
		while (count2 < 4)
		{
			result.array[count2][count] = mat.array[count][count2];
			count2++;
		}
		count++;
	}
	return (result);
}

int	get_determinant_2X2_matrix(t_canva mat)
{
	return((mat.array[0][0] * mat.array[1][1]) - 
        	(mat.array[0][1] * mat.array[1][0]));
}

t_canva get_submatrix(t_canva matrix, int row, int column)
{
	t_canva submatrix;
	int count;
	int count2;
	int count3;
	int count4;

	submatrix = create_canva(matrix.shape[0] - 1, matrix.shape[1] - 1);
	count = 0;
	count2 = 0;
	count3 = 0;
	count4 = 0;
	while (count < matrix.shape[0])
	{
		if (count != row)
		{
			count2 = 0;
			count4 = 0;
			while (count2 < matrix.shape[1])
			{
				if (count2 != column && count3 < submatrix.shape[0] && count4 < submatrix.shape[1])
				{
					submatrix.array[count3][count4] = matrix.array[count][count2];
					count4++;
				}
				count2++;
			}
			count3++;
		}
		count++;
	}
	return (submatrix);
}

int	get_minor_3X3_matrix(t_canva mat, int row, int column)
{
	t_canva submatrix;

	submatrix = get_submatrix(mat, row, column);
	return (get_determinant_2X2_matrix(submatrix));
}

int	get_cofactor_3X3_matrix(t_canva mat, int row, int column)
{
	int minor;

	minor = get_minor_3X3_matrix(mat, row, column);
	if ((row + column) % 2)
		return (-minor);
	else
		return (minor);
}

int	get_determinant_3X3_matrix(t_canva mat, int row, int column)
{
	int cofactor1;
	int cofactor2;
	int cofactor3;

	if (row >= 3 && column % 2)
		row = 2;
	cofactor1 = get_cofactor_3X3_matrix(mat, row, 0);
	cofactor2 = get_cofactor_3X3_matrix(mat, row, 1);
	cofactor3 = get_cofactor_3X3_matrix(mat, row, 2);
	if (row >= 3)
		row = 2;
	return (mat.array[row][0] * cofactor1 +
	        mat.array[row][1] * cofactor2 +
	        mat.array[row][2] * cofactor3);
}

int	get_minor_4X4_matrix(t_canva mat, int row, int column)
{
	t_canva submatrix;

	submatrix = get_submatrix(mat, row, column);
	return (get_determinant_3X3_matrix(submatrix, row, column));
}

int	get_cofactor_4X4_matrix(t_canva mat, int row, int column)
{
	int	minor;

	minor = get_minor_4X4_matrix(mat, row, column);
	if (row == 3)
		return (minor);
	if ((row + column) % 2)
		return (-minor);
	else
		return (minor);
}

int	get_determinant_4X4_matrix(t_canva mat, int row)
{
	int cofactor1;
	int cofactor2;
	int cofactor3;
	int cofactor4;

	if (row >= 3)
		row = 2;
	cofactor1 = get_cofactor_4X4_matrix(mat, row, 0);
	cofactor2 = get_cofactor_4X4_matrix(mat, row, 1);
	cofactor3 = get_cofactor_4X4_matrix(mat, row, 2);
	cofactor4 = get_cofactor_4X4_matrix(mat, row, 3);
	return (mat.array[row][0] * cofactor1 +
	        mat.array[row][1] * cofactor2 +
	        mat.array[row][2] * cofactor3 +
	        mat.array[row][3] * cofactor4);
}

int	matrix_4X4_isinvertible(t_canva mat)
{
	int determinant;

	determinant = get_determinant_4X4_matrix(mat, 0);
	if (determinant == 0)
		return (0);
	else
		return (1);
}

t_canva	inverse_matrix_4X4(t_canva mat)
{
	t_canva result;
	t_canva result_transpose;
	int     count;
	int     count2;
	int     determinant;

	result = create_canva(4, 4);
	count = 0;
	while (count < 4)
	{
		count2 = 0;
		while (count2 < 4)
		{
			result.array[count][count2] = get_cofactor_4X4_matrix(mat, count, count2);
			count2++;
		}
		count++;
	}
	result_transpose = transpose_4X4_matrix(result);
	determinant = get_determinant_4X4_matrix(mat, 3);
	count = 0;
	count2 = 0;
	while (count < 4)
	{
		count2 = 0;
		while (count2 < 4)
		{
			result_transpose.array[count][count2] = result_transpose.array[count][count2] / (double)determinant;
			count2++;
		}
		count++;
	}
	return (result_transpose);
}