/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:57:17 by nojia             #+#    #+#             */
/*   Updated: 2024/11/15 11:00:44 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	is_rt(char *map_name)
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

int	char_not_recognized(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
			return (1);
		i++;	
	}
	return (0);
}

size_t	size_double_tab(char **tab)
{
	size_t	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

int	parse_rgb(char *line)
{
	int	i;
	int	j;
	int	comma;

	comma = 0;
	if (char_not_recognized(line, "0123456789,") || (ft_strlen(line) < 5
		|| ft_strlen(line) > 11))
		return (0);
	i = -1;
	while (line[++i])
		if (line[i] == ',' && ++comma)
			if (i == 0 || !ft_isdigit(line[i - 1]) || !ft_isdigit(line[i + 1]))
				return (0);
	if (comma != 2)
		return (0);
	i = -1;
	j = -1;
	while (++i < 3)
	{
		if (ft_atoi(line + j + 1) > 255)
			return (0);
		while (line[++j] && line[j] != ',')
			;
	}
	return (1);
}

int	parse_range(char *line, double min, double max, int nmemb)
{
	int	i;
	int	j;
	int	comma;

	comma = 0;
	if (char_not_recognized(line, "0123456789.,-") || !parse_nbr_dot(line))
		return (0); 
	i = -1;
	while (line[++i])
		if (line[i] == ',' && ++comma)
			if (i == 0 || !ft_strchr("0.123456789-", line[i - 1])
				|| !ft_strchr("0.123456789-", line[i - 1]))
				return (0);
	if (comma != nmemb - 1)
		return (0);
	i = -1;
	j = -1;
	while (++i < nmemb)
	{
		if (atod(line + j + 1) < min || atod(line + j + 1) > max)
			return (0);
		while (line[++j] && line[j] != ',')
			;
	}
	return (1);
}
