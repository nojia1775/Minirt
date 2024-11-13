/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:12:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/13 21:34:50 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_ambient(char **datas, t_minirt *minirt)
{
	if (size_double_tab(datas) != 3)
		return (0);
	if (!parse_range(datas[1], 0.0, 1.0, 1))
		return (0);
	if (!parse_rgb(datas[2]))
		return (0);
	minirt->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	if (!minirt->ambient)
		return (0);
	minirt->ambient->ambient = atod(datas[1]);
	get_three_int(minirt->ambient->rgb, datas[2]);
	return (1);
}

int	get_camera(char **datas, t_minirt *minirt)
{
	if (size_double_tab(datas) != 4)
		return (0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (0);
	if (!parse_range(datas[2], -1.0, 1.0, 3))
		return (0);
	if (!parse_range(datas[3], 0.0, 180.0, 1))
		return (0);
	minirt->camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!minirt->camera)
		return (0);
	get_three_double(minirt->camera->xyz, datas[1]);
	get_three_double(minirt->camera->vector_xyz, datas[2]);
	minirt->camera->fov = atod(datas[3]);
	return (1);
}

int	get_light(char **datas, t_minirt *minirt)
{
	if (size_double_tab(datas) != 4)
		return (0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (0);
	if (!parse_range(datas[2], 0.0, 1.0, 1))
		return (0);
	if (!parse_rgb(datas[3]))
		return (0);
	minirt->light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (minirt->light == NULL)
		return (0);
	get_three_double(minirt->light->xyz, datas[1]);
	minirt->light->luminosity = atod(datas[2]);
	get_three_int(minirt->light->rgb, datas[3]);
	return (1);
}