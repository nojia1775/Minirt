/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/26 18:09:36 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# define WIDTH 500
# define HEIGHT 500

# define ESC 65307

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

typedef struct s_tuple
{
	double coor[4];
}	t_tuple;

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
	t_tuple	vector_xyz;
	double	fov_x;
	double	fov_y;
}	t_camera;

typedef struct s_canva
{
	int	shape[2];
	int	**array;
}	t_canva;

typedef struct s_matrix
{
	int	shape[3];
	int	***array;
}	t_matrix;

typedef struct s_shape
{
	size_t	index;
	double		xyz[3];
	t_uint8	rgb[3];
	double		height;
	double		diameter;
	double		vector_xyz[3];
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

typedef	struct s_projectile
{
	t_tuple	*position;
	t_tuple *velocity;
}	t_projectile;

typedef	struct s_environment
{
	t_tuple	*gravity;
	t_tuple *wind;
}	t_environment;


//vector_utils
t_tuple	*create_tuple(double x, double y, double z, int w);
typedef struct s_file_rt
{
	char	**line; 
	struct s_file_rt	*next;
}	t_file_rt;

//color utils
int	create_trgb(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

// yann
t_vector	*create_vector(double x, double y, double z);

//tuple_operation
t_tuple	*vec_add_nbr(t_tuple *vec, double nbr);
t_tuple	*vec_add_vec(t_tuple *vec, t_tuple *add);
t_tuple	*vec_sub_vec(t_tuple *vec, t_tuple *add);
double		vec_magnitude(t_tuple *vec);
double		dot_product(t_tuple *first, t_tuple *second, int length);
t_tuple	*vec_normalization(t_tuple *vec);
t_tuple	*vec_multiplication(t_tuple *vec, double scalar);

//projectile
t_projectile	*create_projectile(t_tuple *position, t_tuple *velocity);
t_environment	*create_environment(t_tuple *gravity, t_tuple *wind);
t_projectile	*tick(t_environment *env, t_projectile *proj);

//canva
t_canva		*alloc_canva(t_canva *can, int x, int y);
t_canva		create_canva(int x, int y);
void		display_canva(t_canva *can);
int			compare_2Dmatrix(t_canva *can1, t_canva *can2);

//matrix
t_matrix	*alloc_matrix(t_matrix *mat, int x, int y, int z);
t_matrix	create_matrix(int x, int y, int z);
void		display_mat2d(t_matrix *mat, int axis_1, int axis_2, int slice_axis_3);

//matrix_utils
t_canva    	multiplying_4X4_matrix(t_canva *mat1, t_canva *mat2);
t_tuple		*multiplying_matrix_tuple(t_canva *mat, t_tuple tup);
t_canva		transpose_4X4_matrix(t_canva mat);
int			get_determinant_2X2_matrix(t_canva mat);
t_canva		get_submatrix(t_canva matrix, int row, int column);
int			get_minor_3X3_matrix(t_canva mat, int row, int column);
int			get_cofactor_3X3_matrix(t_canva mat, int row, int column);
int			get_determinant_3X3_matrix(t_canva mat, int row);
int			get_minor_4X4_matrix(t_canva mat, int row, int columns);
int			get_cofactor_4X4_matrix(t_canva mat, int row, int column);
int			get_determinant_4X4_matrix(t_canva mat, int row);
int			matrix_4X4_isinvertible(t_canva mat);
t_canva		inverse_matrix_4X4(t_canva mat);

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

// display
void	display(t_minirt *minirt);
int		put_one_color(t_minirt *minirt, int r, int g, int b);
void	put_pixel_projectile(t_minirt *minirt, int height, int r, int g, int b);

int		convert_rgb(t_uint8 rgb[3]);
double	convert_rad(double deg);
double	convert_deg(double rad);
t_vector vec_add_vec2(t_vector vec, t_vector add);
t_point	apply_vec_to_nbr(t_vector vec, t_point point);
t_vector	vec_multiplication2(t_vector vec, double nbr);
t_tuple	vec_normalization2(t_tuple vec);
t_tuple	vec_cross(t_tuple a, t_tuple b);
double	double_abs(double x);

#endif