/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 17:30:33 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_minirt(t_minirt *minirt)
{
	minirt->ambient = NULL;
	minirt->camera = NULL;
	minirt->cylinder = NULL;
	minirt->light = NULL;
	minirt->plan = NULL;
	minirt->sphere = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_minirt	minirt;
	t_file_rt	*data;
	
	data = NULL;
	init_minirt(&minirt);
	if (!parsing(argc, argv, env, &data))
		return (printf("Error\n"), free_minirt(&minirt), 1);
	if (data == NULL)
		return (42);
	t_file_rt *cur = data;
	while (cur)
	{
		printf("%s\n", cur->line);
		cur = cur->next;
	}
	free_list(data);
	return (0);
}