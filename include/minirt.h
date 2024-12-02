/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/12/02 15:37:16 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# define WIDTH 1000
# define HEIGHT 700

# define AZERTY 0
# define QWERTY 1

# define ESC 65307
# define A_RIGHT 65363
# define A_UP 65362
# define A_LEFT 65361
# define A_DOWN 65364
# if AZERTY
#  define UP 122
#  define DOWN 115
#  define LEFT 113
#  define RIGHT 100
# elif QWERTY
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
# endif
# define ENTER 65293
# define SPACE 32
# define TAB 65289

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
	double	focal_length;
}	t_camera;

typedef struct s_canva
{
	int		shape[2];
	double	**array;
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
	void	*addr_img;
	char	*img;
	int		bits;
	int		size_line;
	int		endian;
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
t_tuple		*vec_add_nbr(t_tuple *vec, double nbr);
t_tuple		*vec_add_vec(t_tuple *vec, t_tuple *add);
t_tuple		*vec_sub_vec(t_tuple *vec, t_tuple *add);
double		vec_magnitude(t_tuple *vec);
double		dot_product(t_tuple *first, t_tuple *second, int length);
t_tuple		*vec_normalization(t_tuple *vec);
t_tuple		*vec_multiplication(t_tuple *vec, double scalar);
t_tuple		negate_tuple(t_tuple tuple);

//matrix transformation
t_canva		translation(double x, double y, double z);
t_canva		scaling(double x, double y, double z);
t_canva		rotation_x(double radian);
t_canva		rotation_y(double radian);
t_canva		rotation_z(double radian);
t_canva	shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);


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
int			get_determinant_3X3_matrix(t_canva mat, int row, int column);
int			get_minor_4X4_matrix(t_canva mat, int row, int columns);
int			get_cofactor_4X4_matrix(t_canva mat, int row, int column);
int			get_determinant_4X4_matrix(t_canva mat, int row);
int			matrix_4X4_isinvertible(t_canva mat);
t_canva		inverse_matrix_4X4(t_canva mat);

//test
void		test_multiply_matrix(void);
void		test_multiply_matrix_4X4_by_tuple(void);
void		transposing_matrix_4X4(void);
void		test_determinant_2X2_matrix(void);
void		test_submatrix_of_3X3_matrix(void);
void		test_submatrix_of_4X4_matrix(void);
void		test_minor_3X3_matrix(void);
void		test_cofactor_3X3_matrix(void);
void		test_determinant_3X3_matrix(void);
void		test_determinant_of_4X4_matrix(void);
void		test1_invert_4X4_matrix(void);
// void		test2_invert_4X4_matrix(void);
void		test_multiply_product_by_inverse(void);
void		test_translation_matrix(void);
void		test_scaling_matrix(void);
void		test_rotation_matrix(void);
void		test_shearing_matrix(void);
void		test_chaining_matrix(void);


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
t_tuple	vec_normalization2(t_tuple vec);
t_tuple	vec_cross(t_tuple a, t_tuple b);
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
void	cam_look_leftright(t_minirt *minirt, double angle);
void	cam_look_updown(t_minirt *minirt, double angle);
void	cam_go_frontback(t_minirt *minirt, int dir);
void	print_coor(void *coor);
void	cam_go_leftright(t_minirt *minirt, int left_right);
void	cam_go_updown(t_minirt *minirt, int up_down);
double	intersec_cylinder(t_minirt *minirt, t_vector pixel, t_shape cylinder);
double	vec_magnitude2(t_vector vec);
void	my_mlx_new_img(t_minirt *minirt);

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