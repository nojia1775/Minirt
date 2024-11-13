/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:05:18 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/13 21:37:47 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	extract_file(char *file, t_file_rt **data)
{
	int	fd;
	char	**line;
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
			line = ft_split(tmp, " \t\n");
			if (!line || char_not_recognized(tmp, "ACLplcys0123456789-., \t\n"))
				return (free(tmp), free_list(data), 0);
			add_list(data, line);
			free(line);
		}
		free(tmp);
	}
	return (1);
}

static int	parse_datas(t_file_rt *data, t_minirt *minirt)
{
	t_file_rt	*cur;
	int			success;

	cur = data;
	if (!cur)
		return (0);
	while (cur)
	{
		if (!ft_strncmp(cur->line[0], "A", 2))
			success = get_ambient(cur->line, minirt);
		else if (!ft_strncmp(cur->line[0], "C", 2))
			success = get_camera(cur->line, minirt);
		else if (!ft_strncmp(cur->line[0], "L", 2))
			success = get_light(cur->line, minirt);
		if (!success)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int	parsing(int argc, char **argv, char **env, t_minirt *minirt)
{
	t_file_rt	*data;

	data = NULL;
	if (argc != 2 || !env[0])
		return (0);
	if (!is_rt(argv[1]))
		return (0);
	if (!extract_file(argv[1], &data))
		return (0);
	if (!parse_datas(data, minirt))
		return (free_list(&data), 0);
	printf("%f %f %f %f %d %d %d\n", minirt->light->xyz[0], minirt->light->xyz[1], minirt->light->xyz[2], minirt->light->luminosity, minirt->light->rgb[0], minirt->light->rgb[1], minirt->light->rgb[2]);
	free_list(&data);
	return (1);
}