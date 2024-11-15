/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/15 16:35:47 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	display(t_minirt *minirt)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			int x = j - WIDTH / 2;
			int y = i - HEIGHT / 2;
			// if (i - WIDTH / 2 == 0 && j - HEIGHT / 2 == 0)
			// 	mlx_pixel_put(minirt->mlx, minirt->win, j, i, 0xFF0000);
			if (sqrt(pow(x, 2) + pow(y, 2)) <= minirt->sphere->diameter / 2)
			{
				mlx_pixel_put(minirt->mlx, minirt->win, j, i, convert_rgb(minirt->sphere->rgb));
			}
			j++;
		}
		i++;
	}
}