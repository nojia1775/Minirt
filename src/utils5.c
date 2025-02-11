/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:17:24 by nojia             #+#    #+#             */
/*   Updated: 2025/02/09 20:21:08 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	parse_range2(char *line, double min, double max, int nmemb)
{
	int		i;
	int		j;
	int		index_value;
	double	values[3];

	index_value = 0;
	i = -1;
	j = -1;
	while (++i < nmemb)
	{
		if (atod(line + j + 1) < min || atod(line + j + 1) > max)
			return (0);
		values[index_value++] = atod(line + j + 1);
		while (line[++j] && line[j] != ',')
			;
	}
	if (nmemb == 3 && values[0] == 0 && values[1] == 0 && values[2] == 0)
		return (-1);
	return (1);
}
