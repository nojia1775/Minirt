/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canva.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:55:35 by yrio              #+#    #+#             */
/*   Updated: 2025/01/22 12:34:38 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// t_canva *alloc_canva(t_canva *can, int x, int y)
// {
// 	int	count;

// 	can = malloc(sizeof(t_canva));
// 	can->shape[0] = x;
// 	can->shape[1] = y;
// 	can->array = (double **)malloc((can->shape[0] + 1) * sizeof(double *));
// 	count = 0;
// 	while (count < can->shape[0])
// 	{
// 		can->array[count] = (double *)malloc((can->shape[1] + 1) * sizeof(double));
// 		count++;
// 	}
// 	return (can);
// }

t_canva create_canva_2X2(void)
{
	t_canva	can;
	int			count;
	int			count2;

	count = 0;
	while (count < 2)
	{
		count2 = 0;
		while (count2 < 2)
		{
			can.array[count][count2] = 0;
			count2++;
		}
		count++;
	}
	return (can);
}

t_canva create_canva_3X3(void)
{
	t_canva	can;
	int			count;
	int			count2;

	count = 0;
	while (count < 3)
	{
		count2 = 0;
		while (count2 < 3)
		{
			can.array[count][count2] = 0;
			count2++;
		}
		count++;
	}
	return (can);
}

t_canva create_canva_4X4(void)
{
	t_canva		can;
	int			count;
	int			count2;

	count = 0;
	while (count < 4)
	{
		count2 = 0;
		while (count2 < 4)
		{
			can.array[count][count2] = 0;
			count2++;
		}
		count++;
	}
	return (can);
}

// t_canva create_canva(int x, int y)
// {
// 	t_canva	*can;
// 	int			count;
// 	int			count2;

// 	can = NULL;
// 	can = alloc_canva(can, x, y);
// 	count = 0;
// 	while (count < x)
// 	{
// 		count2 = 0;
// 		while (count2 < y)
// 		{
// 			can->array[count][count2] = 0;
// 			count2++;
// 		}
// 		count++;
// 	}
// 	return (*can);
// }

void	display_canva(t_canva *can)
{
	int	count;
	int	count2;

	count = 0;
	while (count < can->shape[0])
	{
		count2 = 0;
		while (count2 < can->shape[1])
		{
			printf("%f", can->array[count][count2]);
			count2++;
		}
		printf("\n");
		count++;
	}
}

int	compare_2Dmatrix(t_canva *can1, t_canva *can2)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (count < can1->shape[0])
	{
		count2 = 0;
		while (count2 < can2->shape[1])
		{
			if ((int)(can1->array[count][count2] + 0.5) != (int)(can2->array[count][count2] + 0.5))
				return (0);
			count2++;
		}
		count++;
	}
	return (1);
}