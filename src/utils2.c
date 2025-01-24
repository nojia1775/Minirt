/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:12:35 by nojia             #+#    #+#             */
/*   Updated: 2025/01/24 11:50:48 by nojia            ###   ########.fr       */
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

int	parse_nbr_dot(char *str)
{
	int	i;
	int	dot;

	dot = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			dot++;
			if (i == 0 || !ft_isdigit(str[i - 1]) || str[i + 1] == '\0'
				|| !ft_isdigit(str[i + 1]))
				return (printf("%s %c %c %c\n", str, str[i - 1], str[i], str[i + 1]), 0);
		}
		if (str[i] == ',')
		{
			if (dot > 1)
				return (0);
			dot = 0;
		}
		i++;
	}
	if (dot > 1)
		return (0);
	return (1);
}

t_shape	*get_this_shape(t_shape *shape, size_t index)
{
	t_shape	*cur;

	cur = shape;
	while (cur && cur->index != index)
		cur = cur->next;
	if (cur == NULL)
		return (NULL);
	return (cur);
}

int	convert_rgb(t_uint8 rgb[3])
{
	return (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
