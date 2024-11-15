/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:44:39 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/15 13:45:09 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_list_data(t_file_rt **list)
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

void	add_list_data(t_file_rt **data, char **content)
{
	t_file_rt	*new;
	t_file_rt	*cur;

	new = (t_file_rt *)malloc(sizeof(t_file_rt));
	if (!new)
		return (free_list_data(data));
	new->line = tabdup(content);
	if (!new->line)
		return (free_list_data(data));
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

void	add_list_shape(t_shape **shape)
{
	t_shape	*cur;
	t_shape	*new;

	new = (t_shape *)ft_calloc(1, sizeof(t_shape));
	if (!new)
		return (free_list_shape(shape));
	new->next = NULL;
	cur = *shape;
	if (!cur)
	{
		new->index = 0;
		*shape = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->index = cur->index + 1;

}

void	free_list_shape(t_shape **shape)
{
	t_shape	*cur;
	t_shape	*rm;

	if (!(*shape))
		return ;
	cur = *shape;
	while (cur)
	{
		rm = cur;
		cur = cur->next;
		free(rm);
	}
	*shape = NULL;
}