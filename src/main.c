/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:01:57 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 12:11:43 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv, char **env)
{
	if (!parsing(argc, argv, env))
		return (printf("Error\n"), 1);
	return (0);
}