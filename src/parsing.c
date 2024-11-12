/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:05:18 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 12:51:23 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	is_rt(char *map_name)
{
	int	i;

	i = 0;
	if (ft_strlen(map_name) < 4)
		return (0);
	while (map_name[i])
		i++;
	i -= 3;
	if (ft_strncmp(&map_name[i], ".rt", 3))
		return (0);
	return (1);
}

int	parsing(int argc, char **argv, char **env)
{
	if (argc != 2 || !env[0])
		return (0);
	if (!is_rt(argv[1]))
		return (0);
	return (1);
}