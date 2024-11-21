/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/21 16:24:10 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# define WIDTH 500
# define HEIGHT 500

# define ESC 65307
# define RIGHT 65363
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define Z 122
# define S 115
# define Q 113
# define D 100
# define ENTER 65293
# define SPACE 32
# define SHIFT 65505

# define PI 3.14159265358979323846

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef unsigned char	t_uint8;

typedef struct s_point
{
	double	coor[3];
}	t_point;

typedef struct s_vector
{
	double coor[3];
}	t_vector;

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
	t_point	xyz;
	t_vector	vector_xyz;
	double	fov_x;
	double	fov_y;
	double	focal_length;
}	t_camera;

typedef struct s_matrix
{
	int	shape[3];
	int	***array;
}	t_matrix;

typedef struct s_shape
{
	size_t	index;
	t_point	xyz;
	t_uint8	rgb[3];
	double		height;
	double		diameter;
	t_vector		vector_xyz;
	t_matrix	*mat;
	struct s_shape	*next;
}	t_shape;

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	t_shape		*sphere;
	t_shape		*plan;
	t_shape		*cylinder;
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
}	t_minirt;

typedef struct s_file_rt
{
	char	**line; 
	struct s_file_rt	*next;
}	t_file_rt;

// yann
t_vector	*create_vector(double x, double y, double z);

//vector_operation
t_vector	*vec_add_nbr(t_vector *vec, double nbr);
t_vector	*vec_add_vec(t_vector *vec, t_vector *add);
t_vector	*vec_sub_vec(t_vector *vec, t_vector *add);
double		vec_magnitude(t_vector *vec);
double		dot_product(t_vector *first, t_vector *second, int length);
t_vector	*vec_normalization(t_vector *vec);
t_vector	*vec_multiplication(t_vector *vec, double scalar);

//matrix
t_matrix	*alloc_matrix(t_matrix *mat, int x, int y, int z);
t_matrix	create_matrix(int x, int y, int z);
void		display_mat2d(t_matrix *mat, int axis_1, int axis_2, int slice_axis_3);

//sphere
t_shape		create_sphere(int height);

// noah
int		parsing(int argc, char **argv, char **env, t_minirt *minirt);
void	free_minirt(t_minirt *minirt);
size_t	strlen_to_space(char *str);
double	atod(char *nptr);
void	add_list_data(t_file_rt **list, char **content);
void	free_list_data(t_file_rt **list);
int		extract_file(char *file, t_file_rt **data);
char	**tabdup(char **tab);
int		is_not_empty(char *str);
int		is_rt(char *map_name);
int		char_not_recognized(char *str, char *set);
size_t	size_double_tab(char **tab);
int		parse_rgb(char *line);
int		parse_range(char *line, double min, double max, int nmemb);
int		get_ambient(char **datas, t_minirt *minirt);
void	get_three_double(double *tab, char *line);
void	get_three_int(t_uint8 *tab, char *line);
int	get_camera(char **datas, t_minirt *minirt);
int		get_light(char **datas, t_minirt *minirt);
void	add_list_shape(t_shape **shape);
void	free_list_shape(t_shape **shape);
int		get_sphere(char **datas, t_minirt *minirt);
int		parse_nbr_dot(char *str);
int		get_plan(char **datas, t_minirt *minirt);
int		get_cylinder(char **datas, t_minirt *minirt);
t_shape	*get_this_shape(t_shape *shape, size_t index);
void	my_mlx_init(t_minirt *minirt);
void	my_mlx_new_window(t_minirt *minirt, int width, int height, char *title);
void	display(t_minirt *minirt);
int		convert_rgb(t_uint8 rgb[3]);
double	convert_rad(double deg);
double	convert_deg(double rad);
t_vector vec_add_vec2(t_vector vec, t_vector add);
t_point	apply_vec_to_nbr(t_vector vec, t_point point);
t_vector vec_multiplication2(t_vector vec, double nbr);
t_vector	vec_normalization2(t_vector vec);
t_vector	vec_cross(t_vector a, t_vector b);
double	double_abs(double x);
t_vector	create_vector2(double x, double y, double z);
t_vector	get_pixel_vector(t_minirt *minirt, int x, int y);
double	intersec_sphere(t_minirt *minirt, t_vector pixel, t_shape sphere);
double	get_min(double a, double b);
double	get_max(double a, double b);
void	display_precision(t_minirt *minirt);
double	dot_product2(t_vector a, t_vector b);
t_vector	vec_sub_vec2(t_vector a, t_vector b);
double	intersec_plan(t_minirt *minirt, t_vector pixel, t_shape plan);
void	cam_around_y(t_minirt *minirt, double angle);
void	cam_look_updown(t_minirt *minirt, double angle);
void	cam_go_front(t_minirt *minirt);
void	cam_go_back(t_minirt *minirt);
void	print_coor(void *coor);

#endif