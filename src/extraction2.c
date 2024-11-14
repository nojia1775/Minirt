/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:04:38 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 16:39:52 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_cylinder(char **datas, t_minirt *minirt)
{
	t_shape	*cur;
	
	if (size_double_tab(datas) != 6
		|| !parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (0);
	if (!parse_range(datas[2], -1.0, 1.0, 3))
		return (0);
	if (!parse_range(datas[3], 0, DBL_MAX, 1))
		return (0);
	if (!parse_range(datas[4], 0, DBL_MAX, 1))
		return (0);
	if (!parse_rgb(datas[5]))
		return (0);
	add_list_shape(&minirt->cylinder);
	if (minirt->cylinder == NULL)
		return (0);
	cur = minirt->cylinder;
	while (cur->next)
		cur = cur->next;
	get_three_double(cur->xyz, datas[1]);
	get_three_double(cur->vector_xyz, datas[2]);
	cur->diameter = atod(datas[3]);
	cur->height = atod(datas[4]);
	get_three_int(cur->rgb, datas[5]);
	return (1);
}
