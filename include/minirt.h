/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/12 16:27:19 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef unsigned char	t_uint8;

typedef struct s_light
{
	double		xyz[3];
	double		luminosity;
	t_uint8	rgb[3];
}	t_light;

typedef struct s_ambient
{
	double		ambient;
	t_uint8	rgb[3];
}	t_ambient;

typedef struct s_camera
{
	double		xyz[3];
	double		vector_xyz[3];
	t_uint8	fov;
}	t_camera;

typedef struct s_shape
{
	double		xyz[3];
	t_uint8	rgb[3];
	double		height;
	double		diameter;
	double		vector_xyz[3];
}	t_shape;

typedef struct s_minirt
{
	t_shape		**sphere;
	t_shape		**plan;
	t_shape		**cylinder;
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
}	t_minirt;

typedef struct s_file_rt
{
	char	*line;
	struct s_file_rt	*next;
}	t_file_rt;

int		parsing(int argc, char **argv, char **env, t_file_rt **data);
void	free_minirt(t_minirt *minirt);
size_t	strlen_to_space(char *str);
double	atod(char *nptr);
void	add_list(t_file_rt **list, char *content);
void	free_list(t_file_rt *list);
int		extract_file(char *file, t_file_rt **__DECL_SIMD_atan2);

#endif