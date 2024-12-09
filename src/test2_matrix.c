/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:08:19 by yrio              #+#    #+#             */
/*   Updated: 2024/12/09 20:05:06 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minirt.h"

void	test_rayon_position(void)
{
	t_tuple	point;
	t_tuple	point2;
	t_tuple	point3;
	t_tuple	point4;

	t_tuple	*origin = create_tuple(2, 3, 4, 1);
	t_tuple	*direction = create_tuple(1, 0, 0, 0);
	
	t_ray ray;
	ray.origin = *origin;
	ray.direction = *direction;
	point = position_ray(ray, 0);
	point2 = position_ray(ray, 1);
	point3 = position_ray(ray, -1);
	point4 = position_ray(ray, 2.5);
	if (point.coor[0] != 2.0 || point.coor[1] != 3.0 || point.coor[2] != 4.0)
		printf("[KO] test 1 function position rayon\n");
	else if (point2.coor[0] != 3.0 || point2.coor[1] != 3.0 || point2.coor[2] != 4.0)
		printf("[KO] test 2 function position rayon\n");
	else if (point3.coor[0] != 1.0 || point3.coor[1] != 3.0 || point3.coor[2] != 4.0)
		printf("[KO] test 3 function position rayon\n");
	else if (point4.coor[0] != 4.5 || point4.coor[1] != 3.0 || point4.coor[2] != 4.0)
		printf("[KO] test 4 function position rayon\n");
	else
		printf("[OK] test 1, 2, 3 et 4 function position rayon\n");
}

void	test_intersection_sphere(void)
{
	t_tuple	*origin_cam = create_tuple(0, 0, -5, 1);
	t_tuple	*origin_cam2 = create_tuple(0, 1, -5, 1);
	t_tuple	*origin_cam3 = create_tuple(0, 2, -5, 1);
	t_tuple	*origin_cam4 = create_tuple(0, 0, 0, 1);
	t_tuple	*origin_cam5 = create_tuple(0, 0, 5, 1);
	t_tuple	*direction = create_tuple(0, 0, 1, 0);
	
	t_shape	sphere;
	t_intersection *intersections;
	t_intersection *intersections2;
	t_intersection *intersections3;
	t_intersection *intersections4;
	t_intersection *intersections5;

	sphere.xyz = create_tuple2(0.0, 0.0, 0.0);
	sphere.diameter = 2;
	intersections = point_intersection_sphere(*origin_cam, *direction, sphere);
	intersections2 = point_intersection_sphere(*origin_cam2, *direction, sphere);
	intersections3 = point_intersection_sphere(*origin_cam3, *direction, sphere);
	intersections4 = point_intersection_sphere(*origin_cam4, *direction, sphere);
	intersections5 = point_intersection_sphere(*origin_cam5, *direction, sphere);
	if (intersections[0].t != 4.0 ||  intersections[1].t != 6.0)
		printf("[KO] test 1 intersection function\n");
	else if (intersections2[0].t != 5.0 ||  intersections2[1].t != 5.0)
		printf("[KO] test 2 intersection function\n");
	else if (intersections3[0].t != 0.0 ||  intersections3[1].t != 0.0)
		printf("[KO] test 3 intersection function\n");
	else if (intersections4[0].t != -1.0 ||  intersections4[1].t != 1.0)
		printf("[KO] test 4 intersection function\n");
	else if (intersections5[0].t != -6.0 ||  intersections5[1].t != -4.0)
		printf("[KO] test 5 intersection function\n");
	else
		printf("[OK] test 1, 2, 3, 4, 5 intersection function\n");
}

void	test_encapsulates_t_shape(void)
{
	t_intersection	inter1;
	t_intersection	inter2;
	t_intersection	*inter_agr;
	t_shape			sphere;

	sphere.xyz = create_tuple2(0.0, 0.0, 0.0);
	inter1 = create_struct_intersection(1, sphere);
	inter2 = create_struct_intersection(2, sphere);
	inter_agr = aggregating_intersections(inter1, inter2);
	if (inter_agr[0].t != 1 || inter_agr[1].t != 2)
		printf("[KO] aggregate test function\n");
	else
		printf("[OK] Test aggregate function\n");
	
}