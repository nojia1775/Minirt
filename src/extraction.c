/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:12:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/16 22:46:17 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_ambient(char **datas, t_minirt *minirt)
{
	if (minirt->ambient != NULL)
		return (printf("Error : ambient : defined more than 1 time\n"), 0);
	if (size_double_tab(datas) != 3)
		return (printf("Error : ambient : wrong number of information\n"), 0);
	if (!parse_range(datas[1], 0.0, 1.0, 1))
		return (printf("Error : ambient : in ratio\n"), 0);
	if (!parse_rgb(datas[2]))
		return (printf("Error : ambient : in color\n"), 0);
	minirt->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	if (!minirt->ambient)
		return (printf("Error : ambient : alloc failed\n"), 0);
	minirt->ambient->ambient = atod(datas[1]);
	get_three_int(minirt->ambient->rgb, datas[2]);
	return (1);
}

int	get_camera(char **datas, t_minirt *minirt)
{
	double	rad_fov_x;
	double	ratio;
	
	if (minirt->camera != NULL)
		return (printf("Error : camera : defined more than 1 time\n"), 0);
	if (size_double_tab(datas) != 4)
		return (printf("Error : camera : wrong number of information\n"), 0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (printf("Error : camera : in coordinates\n"), 0);
	if (!parse_range(datas[2], -1.0, 1.0, 3))
		return (printf("Error : camera : in vectors\n"), 0);
	if (!parse_range(datas[3], 0.0, 180.0, 1))
		return (printf("Error : camera : in FOV\n"), 0);
	minirt->camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!minirt->camera)
		return (printf("Error : camera : alloc failed\n"), 0);
	get_three_double(minirt->camera->xyz, datas[1]);
	get_three_double(minirt->camera->vector_xyz, datas[2]);
	minirt->camera->fov_x = atod(datas[3]);
	rad_fov_x = convert_rad(minirt->camera->fov_x);
	ratio = WIDTH / HEIGHT;
	minirt->camera->fov_y = 2 * atan((tan(rad_fov_x / 2) / ratio));
	minirt->camera->fov_y = minirt->camera->fov_y * 180 / PI;
	return (1);
}

int	get_light(char **datas, t_minirt *minirt)
{

	if (minirt->light != NULL)
		return (printf("Error : light : defined more than 1 time\n"), 0);
	if (size_double_tab(datas) != 4)
		return (printf("Error : light : wrong number of information\n"), 0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (printf("Error : light : in coordinates\n"), 0);
	if (!parse_range(datas[2], 0.0, 1.0, 1))
		return (printf("Error : light : in luminosity\n"), 0);
	if (!parse_rgb(datas[3]))
		return (printf("Error : light : in color\n"), 0);
	minirt->light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (minirt->light == NULL)
		return (printf("Error : light : alloc failed/n"), 0);
	get_three_double(minirt->light->xyz, datas[1]);
	minirt->light->luminosity = atod(datas[2]);
	get_three_int(minirt->light->rgb, datas[3]);
	return (1);
}

int	get_sphere(char **datas, t_minirt *minirt)
{
	t_shape	*cur;

	if (size_double_tab(datas) != 4)
		return (printf("Error : sphere : wrong number of information\n"), 0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (printf("Error : sphere : in coordinates\n"), 0);
	if (!parse_range(datas[2], 0, DBL_MAX, 1))
		return (printf("Error : sphere : in diameter\n"), 0);
	if (!parse_rgb(datas[3]))
		return (printf("Error : sphere : in color\n"), 0);
	add_list_shape(&minirt->sphere);
	if (minirt->sphere == NULL)
		return (printf("Error : sphere : alloc failed\n"), 0);
	cur = minirt->sphere;
	while (cur->next)
		cur = cur->next;
	get_three_double(cur->xyz, datas[1]);
	cur->diameter = atod(datas[2]);
	get_three_int(cur->rgb, datas[3]);
	return (1);
}

int	get_plan(char **datas, t_minirt *minirt)
{
	t_shape	*cur;

	if (size_double_tab(datas) != 4)
		return (printf("Error : plan : wrong number of information\n"), 0);
	if (!parse_range(datas[1], -DBL_MAX, DBL_MAX, 3))
		return (printf("Error : plan : in coordinates\n"), 0);
	if (!parse_range(datas[2], -1.0, 1.0, 3))
		return (printf("Error : plan : in vectors\n"), 0);
	if (!parse_rgb(datas[3]))
		return (printf("Error : plan : in color\n"), 0);
	add_list_shape(&minirt->plan);
	if (!minirt->plan)
		return (printf("Error : plan : alloc failed\n"), 0);
	cur = minirt->plan;
	while (cur->next)
		cur = cur->next;
	get_three_double(cur->xyz, datas[1]);
	get_three_double(cur->vector_xyz, datas[2]);
	get_three_int(cur->rgb, datas[3]);
	return (1);
}
