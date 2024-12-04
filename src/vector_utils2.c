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

t_tuple normal_vector_sphere(t_shape sphere, t_tuple point)
{
    t_tuple *vector;

    if (sphere.type == 1)
        vector = create_tuple(point.coor[0], point.coor[1], point.coor[2], 1);
    else
        vector = create_tuple(0, 0, 0, 1);
    return (*vector);
}

t_tuple reflect(t_tuple in, t_tuple normal)
{
    return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in, normal))));
}

double  lighting(t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    double  ambient = 0.1;
    double  diffuse = 0.9;
    double  specular = 0.9;

    double effective_color = 1;

    t_tuple lightv = vec_normalization2(*vec_sub_vec(light.xyz, &point));
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
