/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/01/24 11:28:33 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_H

# define MINIRT_H

# define WIDTH 1000
# define HEIGHT 1000

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
# define P 112
# define SPACE 32
# define TAB 65289

# define PI 3.14159265358979323846

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned char	t_uint8;

typedef enum e_type
{
	SPHERE,
	PLAN,
	CYLINDER
}						t_type;

typedef struct s_tuple
{
	double				coor[4];
}						t_tuple;

typedef struct s_ray
{
	t_tuple				origin;
	t_tuple				direction;
}						t_ray;

typedef struct s_light
{
	t_tuple				xyz;
	double				luminosity;
	t_uint8				rgb[3];
}						t_light;

typedef struct s_ambient
{
	double				ambient;
	t_uint8				rgb[3];
}						t_ambient;

typedef struct s_camera
{
	t_tuple				xyz;
	t_tuple				tuple_xyz;
	double				fov_x;
	double				fov_y;
	double				focal_length;
}						t_camera;

typedef struct s_matrix
{
	int					shape[3];
	int					***array;
}						t_matrix;

typedef struct s_canva
{
	int					shape[2];
	double				array[4][4];
}						t_canva;

typedef struct s_shape
{
	size_t				index;
	t_tuple				xyz;
	t_uint8				rgb[3];
	double				height;
	double				diameter;
	t_tuple				tuple_xyz;
	t_matrix			*mat;
	struct s_shape		*next;
	t_type				type;
	double				distance;
	t_canva				transform;
}						t_shape;

typedef struct s_minirt
{
	void				*mlx;
	void				*win;
	void				*addr_img;
	char				*img;
	int					bits;
	int					size_line;
	int					endian;
	double				color;
	t_shape				*sphere;
	t_shape				*plan;
	t_shape				*cylinder;
	t_camera			*camera;
	t_light				*light;
	t_ambient			*ambient;
}						t_minirt;

typedef struct s_file_rt
{
	char				**line;
	struct s_file_rt	*next;
}						t_file_rt;

// yann
t_tuple					*create_tuple(double x, double y, double z, int w);

// tuple_operation
t_tuple					*vec_add_nbr(t_tuple *vec, double nbr);
t_tuple					*vec_add_vec(t_tuple *vec, t_tuple *add);
t_tuple					*vec_sub_vec(t_tuple *vec, t_tuple *add);
double					vec_magnitude(t_tuple *vec);
double					dot_product(t_tuple *first, t_tuple *second,
							int length);
t_tuple					*vec_normalization(t_tuple *vec);
t_tuple					*vec_multiplication(t_tuple *vec, double scalar);

// canva
t_canva					create_canva(void);

t_canva					create_matrix_identity(void);

// noah
int						parsing(int argc, char **argv, char **env,
							t_minirt *minirt);
void					free_minirt(t_minirt *minirt);
size_t					strlen_to_space(char *str);
double					atod(char *nptr);
void					add_list_data(t_file_rt **list, char **content);
void					free_list_data(t_file_rt **list);
int						extract_file(char *file, t_file_rt **data);
char					**tabdup(char **tab);
int						is_not_empty(char *str);
int						is_rt(char *map_name);
int						char_not_recognized(char *str, char *set);
size_t					size_double_tab(char **tab);
int						parse_rgb(char *line);
int						parse_range(char *line, double min, double max,
							int nmemb);
int						get_ambient(char **datas, t_minirt *minirt);
void					get_three_double(double *tab, char *line);
void					get_three_int(t_uint8 *tab, char *line);
int						get_camera(char **datas, t_minirt *minirt);
int						get_light(char **datas, t_minirt *minirt);
void					add_list_shape(t_shape **shape);
void					free_list_shape(t_shape **shape);
int						get_sphere(char **datas, t_minirt *minirt);
int						parse_nbr_dot(char *str);
int						get_plan(char **datas, t_minirt *minirt);
int						get_cylinder(char **datas, t_minirt *minirt);
t_shape					*get_this_shape(t_shape *shape, size_t index);
void					my_mlx_init(t_minirt *minirt);
void					my_mlx_new_window(t_minirt *minirt, int width,
							int height, char *title);
void					display(t_minirt *minirt);
int						convert_rgb(t_uint8 rgb[3]);
double					convert_rad(double deg);
double					convert_deg(double rad);
t_tuple					vec_add_vec2(t_tuple vec, t_tuple add);
t_tuple					apply_vec_to_nbr(t_tuple vec, t_tuple point);
t_tuple					vec_multiplication2(t_tuple vec, double nbr);
t_tuple					vec_normalization2(t_tuple vec);
t_tuple					vec_cross(t_tuple a, t_tuple b);
double					double_abs(double x);
t_tuple					create_tuple2(double x, double y, double z, int w);
t_tuple					get_pixel_tuple(t_minirt *minirt, t_tuple pixel, int x,
							int y);
double					intersec_sphere(t_minirt *minirt, t_ray rayon,
							t_shape sphere);
double					get_min(double a, double b);
double					get_max(double a, double b);
void					display_precision(t_minirt *minirt);
double					dot_product2(t_tuple a, t_tuple b);
t_tuple					vec_sub_vec2(t_tuple a, t_tuple b);
double					intersec_plan(t_minirt *minirt, t_ray rayon,
							t_shape plan);
void					cam_look_leftright(t_minirt *minirt, double angle);
void					cam_look_updown(t_minirt *minirt, double angle);
void					cam_go_frontback(t_minirt *minirt, int dir);
void					print_coor(void *coor);
void					cam_go_leftright(t_minirt *minirt, int left_right);
void					cam_go_updown(t_minirt *minirt, int up_down);
double					intersec_cylinder(t_minirt *minirt, t_ray rayon,
							t_shape cylinder);
double					vec_magnitude2(t_tuple vec);
void					my_mlx_new_img(t_minirt *minirt);
t_tuple					negate_tuple(t_tuple tuple);
t_tuple					normal_tuple_sphere(t_shape sphere,
							t_tuple world_point);
t_canva					multiplying_matrix(t_canva *mat1, t_canva *mat2);
t_tuple					multiplying_matrix_tuple(t_canva mat, t_tuple tup);
void					display_canva(t_canva *can);
t_tuple					reflect(t_tuple in, t_tuple normal);
t_canva					translation(double x, double y, double z);
t_canva					scaling(double x, double y, double z);
t_canva					rotation_x(double radian);
t_canva					rotation_y(double radian);
t_canva					rotation_z(double radian);
t_ray					transform_ray(t_ray ray, t_canva matrix);
double					get_positive_min(double a, double b);

#endif