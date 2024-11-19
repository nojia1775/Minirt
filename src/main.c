/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/19 19:14:25 by nojia            ###   ########.fr       */
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
	else if (key == RIGHT)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[0] += 5;
		display(minirt);
	}
	else if (key == LEFT)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[0] -= 5;
		display(minirt);
	}
	else if (key == UP)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[1] += 5;
		display(minirt);
	}
	else if (key == DOWN)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[1] -= 5;
		display(minirt);
	}
	else if (key == FRONT)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[2] += 5;
		display(minirt);
	}
	else if (key == BACK)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		minirt->camera->xyz.coor[2] -= 5;
		display(minirt);
	}
	else if (key == ENTER)
	{
		mlx_clear_window(minirt->mlx, minirt->win);
		display_precision(minirt);
	}
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
	display(&minirt);
	mlx_loop(minirt.mlx);
	free_minirt(&minirt);
	return (0);
}
