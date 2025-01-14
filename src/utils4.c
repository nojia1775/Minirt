/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:45 by nojia             #+#    #+#             */
/*   Updated: 2025/01/14 16:42:33 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	print_coor(void *coor)
{
	t_tuple	*vec;

	vec = (t_tuple *)coor;
	ft_putnbr_fd(vec->coor[0], 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(vec->coor[1], 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(vec->coor[2], 1);
	ft_putstr_fd("\n", 1);
}