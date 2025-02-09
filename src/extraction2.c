/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:04:38 by nadjemia          #+#    #+#             */
/*   Updated: 2025/02/09 19:49:01 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	add_bases(t_minirt *minirt)
{
	t_shape	*cy;
	t_shape	*plan;

	cy = minirt->cylinder;
	while (cy->next)
		cy = cy->next;
	plan = minirt->plan;
	add_list_shape(&minirt->plan);
	while (plan->next)
		plan = plan->next;
	plan->diameter = cy->diameter;
	plan->xyz = cy->xyz;
	ft_memcpy(&plan->rgb, &cy->rgb, sizeof(plan->rgb));
	plan->tuple_xyz = cy->tuple_xyz;
	plan->type = PLAN;
	add_list_shape(&minirt->plan);
	plan = plan->next;
	plan->diameter = cy->diameter;
	plan->xyz = apply_vec_to_nbr(vec_multiplication2(cy->tuple_xyz, cy->height), cy->xyz);
	ft_memcpy(&plan->rgb, &cy->rgb, sizeof(plan->rgb));
	plan->tuple_xyz = cy->tuple_xyz;
	plan->type = PLAN;
	return (1);
}

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
	get_three_int(cur->rgb, datas[5]);
	cur->close = 0;
	if (!add_bases(minirt))
		return (0);
	return (1);
}
