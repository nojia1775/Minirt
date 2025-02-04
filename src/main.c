/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/04 18:32:36 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

static int	close_win(void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	free_minirt(minirt);
	exit(0);
	return (1);
}

static int	key_pressed(int key, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (key == ESC)
		close_win(minirt);
	return (1);
}

void	init_minirt(t_minirt *minirt)
{
	minirt->ambient = NULL;
	minirt->camera = NULL;
	minirt->cylinder = NULL;
	minirt->light = NULL;
	minirt->plan = NULL;
	minirt->sphere = NULL;
	minirt->mlx = NULL;
	minirt->win = NULL;
	minirt->addr_img = NULL;
	minirt->img = NULL;
	minirt->bits = 0;
	minirt->size_line = 0;
	minirt->color = 0.0;
}

int	main(int argc, char **argv, char **env)
{
	t_minirt	minirt;

	init_minirt(&minirt);
	if (!parsing(argc, argv, env, &minirt))
		return (free_minirt(&minirt), 1);
	my_mlx_init(&minirt);
	my_mlx_new_window(&minirt, WIDTH, HEIGHT, "MINIRT");
	mlx_hook(minirt.win, 17, 0, close_win, &minirt);
	mlx_key_hook(minirt.win, key_pressed, &minirt);
	my_mlx_new_img(&minirt);
	display_precision(&minirt);
	printf("done\n");
	mlx_loop(minirt.mlx);
	free_minirt(&minirt);
	return (0);
}
