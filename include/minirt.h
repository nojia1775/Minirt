/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 12:36:50 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_light
{
	double		xyz[3];
	double		luminosity;
	u_int8_t	rgb[3];
}	t_light;

typedef struct s_ambient
{
	double		ambient;
	u_int8_t	rgb[3];
}	t_ambient;

typedef struct s_camera
{
	double		xyz[3];
	double		vector_xyz[3];
	u_int8_t	fov;
}	t_camera;

typedef struct s_shape
{
	double		xyz[3];
	u_int8_t	rgb[3];
	double		height;
	double		diameter;
	double		vector_xyz[3];
}	t_shape;

typedef struct s_minirt
{
	t_shape		*sphere;
	t_shape		*plan;
	t_shape		*cylinder;
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
}	t_minirt;

int		parsing(int argc, char **argv, char **env);

#endif