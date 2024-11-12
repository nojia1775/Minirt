/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:44:39 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 17:33:17 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_list(t_file_rt *list)
{
	t_file_rt	*cur;
	t_file_rt	*rm;
	
	cur = list;
	if (!cur)
		return ;
	while (cur)
	{
		rm = cur;
		free(rm->line);
		cur = cur->next;
		free(rm);
	}
}

void	add_list(t_file_rt **data, char *content)
{
	t_file_rt	*new;
	t_file_rt	*cur;

	new = (t_file_rt *)malloc(sizeof(t_file_rt));
	if (!new)
		return (free_list(*data));
	new->line = ft_strdup(content);
	if (!new->line)
		return (free_list(*data));
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
