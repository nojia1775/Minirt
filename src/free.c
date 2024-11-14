/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:01:09 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 17:00:48 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	secured_free(void **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
}

void	free_minirt(t_minirt *minirt)
{
	secured_free((void **)&minirt->ambient);
	secured_free((void **)&minirt->camera);
	secured_free((void **)&minirt->light);
	free_list_shape(&minirt->cylinder);
	secured_free((void **)&minirt->cylinder);
	free_list_shape(&minirt->plan);
	secured_free((void **)&minirt->plan);
	free_list_shape(&minirt->sphere);
	secured_free((void **)&minirt->sphere);
}