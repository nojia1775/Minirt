/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:32:29 by nojia             #+#    #+#             */
/*   Updated: 2025/01/21 17:23:30 by nadjemia         ###   ########.fr       */
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

double	get_positive_min(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	else if (a >= 0 && b < 0)
		return (a);
	else if (b >= 0 && a < 0)
		return (b);
	else if (a < b)
		return (a);
	else
		return (b);
}

double	get_max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}
