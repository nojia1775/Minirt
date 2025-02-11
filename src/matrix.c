/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:56:25 by yrio              #+#    #+#             */
/*   Updated: 2025/02/04 17:26:32 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_canva	create_matrix_identity(void)
{
	t_canva	mat_identity;

	mat_identity = create_canva();
	mat_identity.array[0][0] = 1.0;
	mat_identity.array[1][1] = 1.0;
	mat_identity.array[2][2] = 1.0;
	mat_identity.array[3][3] = 1.0;
	return (mat_identity);
}

int	is_matrix_identity(t_canva mat)
{
	if (mat.array[0][0] == 1.0 && mat.array[1][1] == 1.0 &&
		mat.array[2][2] == 1.0 && mat.array[3][3] == 1.0 &&
		mat.array[0][1] == 0.0 && mat.array[0][2] == 0.0 &&
		mat.array[0][3] == 0.0 && mat.array[1][0] == 0.0 &&
		mat.array[1][2] == 0.0 && mat.array[1][3] == 0.0 &&
		mat.array[2][0] == 0.0 && mat.array[2][1] == 0.0 &&
		mat.array[2][3] == 0.0 && mat.array[3][0] == 0.0 &&
		mat.array[3][1] == 0.0 && mat.array[3][2] == 0.0)
		return (1);
	else
		return (0);
}
