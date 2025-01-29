/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:36:14 by yrio              #+#    #+#             */
/*   Updated: 2025/01/29 16:26:14 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple normal_tuple_cylindre(t_shape cy, t_tuple point)
{
    double dist;

    dist = pow(point.coor[0], 2) + pow(point.coor[2], 2);
    if (dist < (cy.diameter / 2) && point.coor[1] >= cy.height - EPSILON)
        return (create_tuple2(0, 1, 0, 0));
    else if (dist < (cy.diameter / 2) && point.coor[1] <= cy.xyz.coor[1] + EPSILON)
        return (create_tuple2(0, -1, 0, 0));
    point.coor[1] = 0;
    point.coor[3] = 0;
    return (point);
}

int check_cap(t_ray rayon, int t, int diametre)
{
    double x;
    double z;

    x = rayon.origin.coor[0] + t * rayon.direction.coor[0];
    z = rayon.origin.coor[2] + t * rayon.direction.coor[2];
    if (pow(x, 2) + pow(z, 2) <= (diametre / 2))
        return (1);
    else
        return (0);
}

int intersect_caps(t_shape cy, t_ray rayon)
{
    double  test_cap;
    int     axis_index;
    double  minimum;
    double  maximum;

    axis_index = 1;
	if (cy.tuple_xyz.coor[0] == 1)
		axis_index = 0;
	minimum = cy.xyz.coor[axis_index];
	maximum = cy.xyz.coor[axis_index] + cy.height;
    test_cap = minimum - rayon.origin.coor[1];
    if (test_cap != 0)
        test_cap = test_cap / rayon.direction.coor[1];
    if (check_cap(rayon, test_cap, cy.diameter))
        return (test_cap);
    test_cap = maximum - rayon.origin.coor[1];
    if (test_cap != 0)
        test_cap = test_cap / rayon.direction.coor[1];
    if (check_cap(rayon, test_cap, cy.diameter))
        return (test_cap);
    return (-1);
}
