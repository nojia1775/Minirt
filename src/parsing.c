/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:05:18 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 17:33:28 by nadjemia         ###   ########.fr       */
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

static int	is_not_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (0);
}

int	extract_file(char *file, t_file_rt **data)
{
	int	fd;
	char	*line;
	char	*tmp;
	
	(void)data;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
 			break ;
		if (is_not_empty(tmp))
		{
			line = ft_strtrim(tmp, " \n\t");
			add_list(data, line);
			free(line);
		}
		free(tmp);
	}
	return (1);
}

int	parsing(int argc, char **argv, char **env, t_file_rt **data)
{
	if (argc != 2 || !env[0])
		return (0);
	if (!is_rt(argv[1]))
		return (0);
	if (!extract_file(argv[1], data))
		return (0);
	return (1);
}