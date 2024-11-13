/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:12:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/13 17:15:03 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_ambient(char **datas, t_minirt *minirt)
{
	int	i;
	
	if (!parse_range(datas[1], 0.0, 1.0, 1))
		return (0);
	if (!parse_rgb(datas[2]))
		return (0);
	minirt->ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!minirt->ambient)
		return (0);
	minirt->ambient->ambient = atod(datas[1]);
	minirt->ambient->rgb[0] = ft_atoi(datas[2]);
	i = 0;
	while (datas[2][i] && datas[2][i] != ',')
		i++;
	minirt->ambient->rgb[1] = ft_atoi(datas[2] + i + 1);
	while (datas[2][++i] && datas[2][i] != ',')
		;
	minirt->ambient->rgb[2] = ft_atoi(datas[2] + i + 1);
	return (1);
}
