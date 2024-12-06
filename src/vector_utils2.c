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

t_tuple normal_vector_sphere(t_shape sphere, t_canva transform, t_tuple world_point)
{
    sphere.xyz.coor[0] = 0.0;
    //t_canva can = translation(sphere.xyz.coor[0], sphere.xyz.coor[1], sphere.xyz.coor[2]);
    t_canva inv_can = inverse_matrix_4X4(transform);
    printf("x : %f, y : %f, z : %f\n", world_point.coor[0], world_point.coor[1], world_point.coor[2]);
    t_tuple *result =  multiplying_matrix_tuple(&inv_can, world_point);
    printf("x : %f, y : %f, z : %f\n", result->coor[0], result->coor[1], result->coor[2]);
    t_canva transpose_inv_can = transpose_4X4_matrix(inv_can);
    display_canva(&transpose_inv_can);
    t_tuple *result_world = multiplying_matrix_tuple(&transpose_inv_can, *result);
    // printf("------0-----\n");
    // printf("x : %f, y : %f, z : %f\n", world_point.coor[0], world_point.coor[1], world_point.coor[2]);
    // printf("-------1----\n");
    // display_canva(&can);
    // printf("------2-----\n");
    // display_canva(&inv_can);
    // printf("------3-----\n");
    // printf("x : %f, y : %f, z : %f\n", result->coor[0], result->coor[1], result->coor[2]);
    // printf("------4-----\n");
    // display_canva(&transpose_inv_can);
    // printf("------5-----\n");
    // printf("x : %f, y : %f, z : %f\n", result_world->coor[0], result_world->coor[1], result_world->coor[2]);
    // printf("------end----\n");
    result_world->coor[3] = 0;
    //t_tuple *normalized_result_world = vec_normalization(result_world);
    return (*result_world);
}

t_tuple reflect(t_tuple in, t_tuple normal)
{
    return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in, normal))));
}

// double  lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_shape *shape)
// {
//     double  ambient = 1;
//     double  diffuse = 1;
//     double  specular = 0;
// 	t_tuple	normal;
// 	t_tuple lightv;
//     //t_tuple pixel = negate_tuple(eyev);
//     double  factor;

// 	if (shape->type == SPHERE)
// 		normal = create_tuple2(point.coor[0] - shape->xyz.coor[0], point.coor[1] - shape->xyz.coor[1], point.coor[2] - shape->xyz.coor[2]);
// 	else
// 		normal = shape->vector_xyz;
//     double effective_color = ((double)shape->rgb[0] / 255) * ((double)minirt->light->rgb[0] / 255) + ((double)shape->rgb[1] / 255) * ((double)minirt->light->rgb[1] / 255) + ((double)shape->rgb[2] / 255) * ((double)minirt->light->rgb[2] / 255);
//     lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
//     ambient = effective_color * ambient;

//     double light_dot_normal = dot_product2(lightv, normal);
//     light_dot_normal = acos(light_dot_normal / (vec_magnitude2(lightv) * vec_magnitude2(normal)));
//     if (light_dot_normal < 0)
//     {
//         diffuse = 0;
//         specular = 0;
//         // if (pixel.coor[0] > 0.72 && pixel.coor[0] < 0.74 && pixel.coor[1] > 0.15 && pixel.coor[1] < 0.18 && pixel.coor[2] > 0.60 && pixel.coor[1] < 0.65)
//         //     printf("a\n");
//     }
//     else
//     {
//         diffuse = effective_color * diffuse * light_dot_normal;
//         t_tuple reflectv = reflect(negate_tuple(lightv), normal);
//         double  reflect_dot_eye = dot_product2(reflectv, eyev);
//         reflect_dot_eye = acos(reflect_dot_eye / (vec_magnitude2(reflectv) * vec_magnitude2(eyev)));
//         if (reflect_dot_eye <= 0)
//             specular = 0;
//         else
//         {
//             factor = pow(reflect_dot_eye, 100.0);
//             specular = 1 * specular * factor; 
//         }
//         // if (pixel.coor[0] > 0.72 && pixel.coor[0] < 0.74 && pixel.coor[1] > 0.15 && pixel.coor[1] < 0.18 && pixel.coor[2] > 0.60 && pixel.coor[1] < 0.65)
//         // {
//         //     printf("--- %f\n", reflect_dot_eye);
//         //     printf("%f %f %f\n", ambient, diffuse, specular);
//         // }
//     }
//     return (ambient + diffuse + specular);
// }

double  lighting(t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    double  ambient = 0.1;
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
