/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/22 15:06:35 by nojia            ###   ########.fr       */
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
		cam_go_leftright(minirt, 1);
	else if (key == LEFT)
		cam_go_leftright(minirt, -1);
	else if (key == UP)
		cam_go_frontback(minirt, 1);
	else if (key == DOWN)
		cam_go_frontback(minirt, -1);
	else if (key == Z)
		cam_look_updown(minirt, -PI / 8.0);
	else if (key == S)
		cam_look_updown(minirt, PI / 8.0);
	else if (key == Q)
		cam_look_leftright(minirt, -PI / 8.0);
	else if (key == D)
		cam_look_leftright(minirt, PI / 8.0);
	else if (key == TAB)
		cam_go_updown(minirt, 1);
	else if (key == SPACE)
		cam_go_updown(minirt, -1);
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
