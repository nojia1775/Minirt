/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:12:35 by nojia             #+#    #+#             */
/*   Updated: 2024/11/13 21:29:53 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	get_three_double(double *tab, char *line)
{
	int	i;

	tab[0] = atod(line);
	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	tab[1] = atod(line + i + 1);
	while (line[++i] && line[i] != ',')
		;
	tab[2] = atod(line + i + 1);
}

void	get_three_int(t_uint8 *tab, char *line)
{
	int	i;

	tab[0] = ft_atoi(line);
	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	tab[1] = ft_atoi(line + i + 1);
	while (line[++i] && line[i] != ',')
		;
	tab[2] = ft_atoi(line + i + 1);
}