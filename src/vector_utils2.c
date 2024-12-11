/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:06:21 by yrio              #+#    #+#             */
/*   Updated: 2024/12/02 11:39:02 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// t_tuple normal_vector_sphere(t_shape sphere, t_tuple point)
// {
//     t_tuple *vector;

//     if (sphere.type == 1)
//         vector = create_tuple(point.coor[0], point.coor[1], point.coor[2], 1);
//     else
//         vector = create_tuple(0, 0, 0, 1);
//     return (*vector);
// }

t_tuple normal_vector_sphere(t_shape sphere, t_tuple world_point)
{
    t_canva inv_can = inverse_matrix_4X4(sphere.transform);
    t_tuple result =  multiplying_matrix_tuple(inv_can, world_point);
    t_canva transpose_inv_can = transpose_4X4_matrix(inv_can);
    t_tuple result_world = multiplying_matrix_tuple(transpose_inv_can, result);
    result_world.coor[3] = 0;
    t_tuple *normalized_result_world = vec_normalization(&result_world);
    return (*normalized_result_world);
}

t_tuple reflect(t_tuple in, t_tuple normal)
{
    return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in, normal))));
}

// double  lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_shape *shape)
// {
//     double  ambient = 1;
//     double  diffuse = 0.9;
//     double  specular = 0.1;
// 	t_tuple	normal;
// 	t_tuple lightv;
//     //t_tuple pixel = negate_tuple(eyev);
//     double  factor;

// 	if (shape->type == SPHERE)
// 		normal = create_tuple2(point.coor[0] - shape->xyz.coor[0], point.coor[1] - shape->xyz.coor[1], point.coor[2] - shape->xyz.coor[2], 0);
// 	else
// 		normal = shape->vector_xyz;
//     normal = vec_normalization2(normal);
//     double effective_color = ((double)shape->rgb[0] / 255) * ((double)minirt->light->rgb[0] / 255) + ((double)shape->rgb[1] / 255) * ((double)minirt->light->rgb[1] / 255) + ((double)shape->rgb[2] / 255) * ((double)minirt->light->rgb[2] / 255);
//     lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
//     ambient = effective_color * ambient;

//     double light_dot_normal = dot_product2(lightv, normal);
//     if (light_dot_normal < 0)
//     {
//         diffuse = 0;
//         specular = 0;
//     }
//     else
//     {
//         diffuse = effective_color * diffuse * light_dot_normal;
//         t_tuple reflectv = reflect(negate_tuple(lightv), normal);
//         reflectv = vec_normalization2(reflectv);
//         eyev = vec_normalization2(eyev);
//         double  reflect_dot_eye = dot_product2(reflectv, eyev);
//         if (reflect_dot_eye <= 0)
//             specular = 0;
//         else
//         {
//             factor = pow(reflect_dot_eye, 100.0);
//             specular = 1 * specular * factor; 
//         }
//     }
//     return (ambient + diffuse + specular);
// }

double  lighting(t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    double  ambient = 0.3;
    double  diffuse = 0.9;
    double  specular = 0.9;
    double effective_color = 1;
    t_tuple lightv = vec_normalization2(vec_sub_vec2(light.xyz, point));
    ambient = effective_color * ambient;
    double light_dot_normal = dot_product2(lightv, normalv);
    if (light_dot_normal < 0)
    {
        diffuse = 0;
        specular = 0;
    }
    else
    {
        diffuse = effective_color * diffuse * light_dot_normal;
        t_tuple reflectv = reflect(negate_tuple(lightv), normalv);
        double  reflect_dot_eye = dot_product2(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = 0;
        else
        {
            double factor = pow(reflect_dot_eye, 200.0);
            specular = 1 * specular * factor; 
        }
    }
    return (ambient + diffuse + specular);
}
