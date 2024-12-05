/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:42:19 by yrio              #+#    #+#             */
/*   Updated: 2024/11/18 17:39:12 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_projectile	*create_projectile(t_tuple *position, t_tuple *velocity)
{
	t_projectile	*projectile;

	projectile = NULL;
	projectile = malloc(2 * sizeof(t_projectile));
	projectile->position = position;
	projectile->velocity = velocity;
	return (projectile);
}

t_environment	*create_environment(t_tuple *gravity, t_tuple *wind)
{
	t_environment	*environment;

	environment = NULL;
	environment = malloc(sizeof(t_environment));
	environment->gravity = gravity;
	environment->wind = wind;
	return (environment);
}

t_projectile	*tick(t_environment *env, t_projectile *proj)
{
	t_tuple	*position;
	t_tuple	*velocity;

	position = vec_add_vec(proj->position, proj->velocity);
	velocity = vec_add_vec(proj->velocity, env->gravity);
	velocity = vec_add_vec(velocity, env->wind);
	return (create_projectile(position, velocity));
}
