/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:32:29 by nojia             #+#    #+#             */
/*   Updated: 2025/01/23 15:42:13 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	convert_rad(double deg)
{
	return (deg * PI / 180);
}

double	convert_deg(double rad)
{
	return (rad * 180 / PI);
}

double	double_abs(double x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

double	get_min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	get_max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}
