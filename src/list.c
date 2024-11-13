/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:44:39 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/13 15:39:15 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_list(t_file_rt **list)
{
	t_file_rt	*cur;
	t_file_rt	*rm;
	int		i;
	
	cur = *list;
	if (!cur)
		return ;
	while (cur)
	{
		rm = cur;
		i = 0;
		while (rm->line[i])
			free(rm->line[i++]);
		free(rm->line);
		cur = cur->next;
		free(rm);
	}
	*list = NULL;
}

void	add_list(t_file_rt **data, char **content)
{
	t_file_rt	*new;
	t_file_rt	*cur;

	new = (t_file_rt *)malloc(sizeof(t_file_rt));
	if (!new)
		return (free_list(data));
	new->line = tabdup(content);
	if (!new->line)
		return (free_list(data));
	new->next = NULL;
	if (!(*data))
		*data = new;
	else
	{
		cur = *data;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}
