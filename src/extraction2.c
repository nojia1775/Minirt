/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:04:38 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/04 17:23:18 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_cylinder(char **datas, t_minirt *minirt)
{
	t_shape	*cur;

	if (size_double_tab(datas) != 6
		|| !parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (printf("Error : cylinder : number or coordinates\n"), 0);
	if (parse_range(datas[2], -1.0, 1.0, 3) < 1)
		return (printf("Error : cylinder : in tuples\n"), 0);
	if (!parse_range(datas[3], 0, DBL_MAX, 1))
		return (printf("Error : cylinder : in diameter\n"), 0);
	if (!parse_range(datas[4], 0, DBL_MAX, 1))
		return (printf("Error : cylinder : in height\n"), 0);
	if (!parse_rgb(datas[5]))
		return (printf("Error : cylinder : in color\n"), 0);
	add_list_shape(&minirt->cylinder);
	if (minirt->cylinder == NULL)
		return (printf("Error : cylinder : alloc failed\n"), 0);
	cur = minirt->cylinder;
	while (cur->next)
		cur = cur->next;
	cur->type = CYLINDER;
	get_three_double(cur->xyz.coor, datas[1]);
	get_three_double(cur->tuple_xyz.coor, datas[2]);
	cur->diameter = atod(datas[3]);
	cur->height = atod(datas[4]);
	cur->close = 0;
	// cur->caps_dist = -1;
	return (get_three_int(cur->rgb, datas[5]), 1);
}
