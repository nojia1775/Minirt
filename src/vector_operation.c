/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:27:13 by yrio              #+#    #+#             */
/*   Updated: 2025/01/09 21:03:05 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	*vec_add_nbr(t_tuple *vec, double nbr)
{
	if (!vec)
		return (NULL);
	vec->coor[0] = vec->coor[0] + nbr;
	vec->coor[1] = vec->coor[1] + nbr;
	vec->coor[2] = vec->coor[2] + nbr;
	return (vec);
}

t_tuple	apply_vec_to_nbr(t_tuple vec, t_tuple point)
{
	t_tuple	result;

	result.coor[0] = point.coor[0] + vec.coor[0];
	result.coor[1] = point.coor[1] + vec.coor[1];
	result.coor[2] = point.coor[2] + vec.coor[2];
	return (result);
}

t_tuple	*vec_add_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] + add->coor[0];
	vec->coor[1] = vec->coor[1] + add->coor[1];
	vec->coor[2] = vec->coor[2] + add->coor[2];
	return (vec);
}

t_tuple	vec_add_vec2(t_tuple vec, t_tuple add)
{
	t_tuple	result;

	result.coor[0] = vec.coor[0] + add.coor[0];
	result.coor[1] = vec.coor[1] + add.coor[1];
	result.coor[2] = vec.coor[2] + add.coor[2];
	return (result);
}

t_tuple	*vec_sub_vec(t_tuple *vec, t_tuple *add)
{
	if (!vec || !add)
		return (NULL);
	vec->coor[0] = vec->coor[0] - add->coor[0];
	vec->coor[1] = vec->coor[1] - add->coor[1];
	vec->coor[2] = vec->coor[2] - add->coor[2];
	return (vec);
}
