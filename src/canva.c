/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canva.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:55:35 by yrio              #+#    #+#             */
/*   Updated: 2025/01/24 11:29:08 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva	create_canva(void)
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
