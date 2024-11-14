/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:05:18 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 17:07:31 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	split = NULL;
}

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
				return (free(tmp), free_split(line), free_list_data(data), 0);
			add_list_data(data, line);
			free_split(line);
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
		else if (!ft_strncmp(cur->line[0], "sp", 3))
			success = get_sphere(cur->line, minirt);
		else if (!ft_strncmp(cur->line[0], "pl", 3))
			success = get_plan(cur->line, minirt);
		else if  (!ft_strncmp(cur->line[0], "cy", 3))
			success = get_cylinder(cur->line, minirt);
		if (!success)
			return (free_minirt(minirt), 0);
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
		return (free_list_data(&data), 0);
	if (!minirt->camera || !minirt->ambient || !minirt->light)
		return (free_list_data(&data), 0);
	free_list_data(&data);
	return (1);
}
