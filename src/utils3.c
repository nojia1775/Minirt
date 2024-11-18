/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:32:29 by nojia             #+#    #+#             */
/*   Updated: 2024/11/17 15:08:11 by nojia            ###   ########.fr       */
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