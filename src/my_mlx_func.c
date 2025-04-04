/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:04:41 by nadjemia          #+#    #+#             */
/*   Updated: 2025/03/21 13:16:07 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	my_mlx_init(t_minirt *minirt)
{
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
	{
		printf("Error : mlx_init() failed\n");
		free_minirt(minirt);
		exit(1);
	}
}

void	my_mlx_new_window(t_minirt *minirt, int width, int height, char *title)
{
	minirt->win = mlx_new_window(minirt->mlx, width, height, title);
	if (!minirt->win)
	{
		printf("Error : mlx_new_window() failed\n");
		mlx_destroy_display(minirt->mlx);
		free_minirt(minirt);
		exit(1);
	}
}

void	my_mlx_new_img(t_minirt *minirt)
{
	minirt->addr_img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (!minirt->addr_img)
	{
		free_minirt(minirt);
		exit(1);
	}
}
