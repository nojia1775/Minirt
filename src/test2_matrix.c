/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:08:19 by yrio              #+#    #+#             */
/*   Updated: 2024/12/10 19:53:59 by yrio             ###   ########.fr       */
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

	t_ray  ray;
	t_ray  ray2;
	t_ray  ray3;
	t_ray  ray4;
	t_ray  ray5;
	
	ray.origin = *origin_cam;
	ray.direction = *direction;
	ray2.origin = *origin_cam2;
	ray2.direction = *direction;
	ray3.origin = *origin_cam3;
	ray3.direction = *direction;
	ray4.origin = *origin_cam4;
	ray4.direction = *direction;
	ray5.origin = *origin_cam5;
	ray5.direction = *direction;
	
	t_shape	sphere;
	t_intersection *intersections;
	t_intersection *intersections2;
	t_intersection *intersections3;
	t_intersection *intersections4;
	t_intersection *intersections5;

	sphere.xyz = create_tuple2(0.0, 0.0, 0.0);
	sphere.diameter = 2;
	sphere.transform = create_matrix_identity();
	intersections = point_intersection_sphere(ray, sphere);
	intersections2 = point_intersection_sphere(ray2, sphere);
	intersections3 = point_intersection_sphere(ray3, sphere);
	intersections4 = point_intersection_sphere(ray4, sphere);
	intersections5 = point_intersection_sphere(ray5, sphere);
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

void	test_hit_function(void)
{
	t_shape			sphere;
	t_intersection	i1;
	t_intersection	i2;
	t_intersection	i3;
	t_intersection	i4;
	t_intersection	i5;
	t_intersection	i6;
	t_intersection	i7;
	t_intersection	xs;
	t_intersection	xs2;
	t_intersection	xs3;
	t_intersection	xs4;
	t_intersection	*inter_agr;
	t_intersection	*inter_agr2;
	t_intersection	*inter_agr3;
	t_intersection	*inter_agr4;
	
	sphere.xyz = create_tuple2(0.0, 0.0, 0.0);
	i1 = create_struct_intersection(1, sphere);
	i2 = create_struct_intersection(2, sphere);
	i3 = create_struct_intersection(-1, sphere);
	i4 = create_struct_intersection(-2, sphere);
	i5 = create_struct_intersection(5, sphere);
	i6 = create_struct_intersection(7, sphere);
	i7 = create_struct_intersection(-3, sphere);
	inter_agr = aggregating_intersections(i1, i2);
	inter_agr2 = aggregating_intersections(i1, i3);
	inter_agr3 = aggregating_intersections(i3, i4);
	inter_agr4 = aggregating_4_intersections(i5, i6, i7, i2);
	xs = hit(inter_agr);
	xs2 = hit(inter_agr2);
	xs3 = hit(inter_agr3);
	xs4 = hit(inter_agr4);
	if (xs.t != 1)
		printf("[KO] test 1 hit function\n");
	else if (xs2.t != 1)
		printf("[KO] test 2 hit function\n");
	else if (xs3.count != 0)
		printf("[KO] test 3 hit function\n");
	else if (xs4.t != 2)
		printf("[KO] test 4 hit function\n");
	else
		printf("[OK] test 1, 2, 3, 4 hit function\n");
}

void	test_transform_ray(void)
{
	t_ray	rayon;
	t_ray	rayon_transform;
	t_ray	rayon_transform2;
	t_tuple	*origin;
	t_tuple	*direction;
	t_canva	transform;
	t_canva	transform2;
	
	origin = create_tuple(1.0, 2.0, 3.0, 1.0);
	direction = create_tuple(0.0, 1.0, 0.0, 1.0);	
	transform = translation(3.0, 4.0, 5.0);
	transform2 = scaling(2.0, 3.0, 4.0);
	rayon.origin = *origin;
	rayon.direction = *direction;
	rayon_transform = transform_ray(rayon, transform);
	rayon_transform2 = transform_ray(rayon, transform2);
	if (rayon_transform.origin.coor[0] != 4.0 || rayon_transform.origin.coor[1] != 6.0 || rayon_transform.origin.coor[2] != 8.0)
		printf("[KO] test 1 transform rayon function\n");
	else if (rayon_transform2.origin.coor[0] != 2.0 || rayon_transform2.origin.coor[1] != 6.0 || rayon_transform2.origin.coor[2] != 12.0
			|| rayon_transform2.direction.coor[0] != 0.0 || rayon_transform2.direction.coor[1] != 3.0 || rayon_transform2.direction.coor[2] != 0.0)
		printf("[KO] test 2 transform rayon function\n");
	else
		printf("[OK] test 1, 2 transform rayon function\n");
}

void	test_transformation_sphere_operation(void)
{
	t_ray			rayon;
	t_tuple			origin;
	t_tuple			direction;
	t_shape			sphere;
	t_intersection	*xs;

	origin = create_tuple2(0.0, 0.0, -5.0);
	direction = create_tuple2(0.0, 0.0, 0.1);
	sphere.transform = scaling(2.0, 2.0, 2.0);
	rayon.origin = origin;
	rayon.direction = direction;
	xs = point_intersection_sphere(rayon, sphere);
	printf("xs 1 : %f, xs 2 : %f\n", xs[0].t, xs[1].t);
}