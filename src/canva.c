/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canva.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:55:35 by yrio              #+#    #+#             */
/*   Updated: 2024/11/18 20:09:13 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva *alloc_canva(t_canva *can, int x, int y)
{
	int	count;

	can = malloc(sizeof(t_canva));
	can->shape[0] = x;
	can->shape[1] = y;
	can->array = (int **)malloc((can->shape[0] + 1) * sizeof(int *));
	count = 0;
	while (count < can->shape[0])
	{
		can->array[count] = (int *)malloc((can->shape[1] + 1) * sizeof(int));
		count++;
	}
	return (can);
}

t_canva create_canva(int x, int y)
{
	t_canva	*can;
	int			count;
	int			count2;

	can = NULL;
	can = alloc_canva(can, x, y);
	count = 0;
	while (count < x)
	{
		count2 = 0;
		while (count2 < y)
		{
			can->array[count][count2] = 0;
			count2++;
		}
		count++;
	}
	return (*can);
}

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
			printf("%d", can->array[count][count2]);
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
			if (can1->array[count][count2] != can2->array[count][count2])
				return (0);
			count2++;
		}
		count++;
	}
	return (1);
}