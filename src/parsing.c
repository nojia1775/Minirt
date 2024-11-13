/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:05:18 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/13 17:17:14 by nojia            ###   ########.fr       */
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

	cur = data;
	if (!cur)
		return (0);
	while (cur)
	{
		if (!ft_strncmp(cur->line[0], "A", 2))
			if (!get_ambient(cur->line, minirt))
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
	printf("%f %d %d %d\n", minirt->ambient->ambient, minirt->ambient->rgb[0], minirt->ambient->rgb[1], minirt->ambient->rgb[2]);
	free_list(&data);
	return (1);
}