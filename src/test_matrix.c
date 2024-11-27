/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:24:00 by yrio              #+#    #+#             */
/*   Updated: 2024/11/27 18:12:54 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minirt.h"

void	test_multiply_matrix(void)
{
	t_canva	can;
	t_canva	can2;
	t_canva	can3;

	can = create_canva(4, 4);
	can.array[0][0] = 1;
	can.array[0][1] = 2;
	can.array[0][2] = 3;
	can.array[0][3] = 4;
	can.array[1][0] = 5;
	can.array[1][1] = 6;
	can.array[1][2] = 7;
	can.array[1][3] = 8;
	can.array[2][0] = 9;
	can.array[2][1] = 8;
	can.array[2][2] = 7;
	can.array[2][3] = 6;
	can.array[3][0] = 5;
	can.array[3][1] = 4;
	can.array[3][2] = 3;
	can.array[3][3] = 2;

	can2 = create_canva(4, 4);
	can2.array[0][0] = -2;
	can2.array[0][1] = 1;
	can2.array[0][2] = 2;
	can2.array[0][3] = 3;
	can2.array[1][0] = 3;
	can2.array[1][1] = 2;
	can2.array[1][2] = 1;
	can2.array[1][3] = -1;
	can2.array[2][0] = 4;
	can2.array[2][1] = 3;
	can2.array[2][2] = 6;
	can2.array[2][3] = 5;
	can2.array[3][0] = 1;
	can2.array[3][1] = 2;
	can2.array[3][2] = 7;
	can2.array[3][3] = 8;

	can3 = multiplying_4X4_matrix(&can, &can2);
	if (can3.array[0][0] != 20 || can3.array[0][1] != 22 || can3.array[0][2] != 50 || can3.array[0][3] != 48)
		printf("[KO] multiply matrix 4X4 function\n");
	else if (can3.array[1][0] != 44 || can3.array[1][1] != 54 || can3.array[1][2] != 114 || can3.array[1][3] != 108)
		printf("[KO] multiply matrix 4X4 function\n");
	else if (can3.array[2][0] != 40 || can3.array[2][1] != 58 || can3.array[2][2] != 110 || can3.array[2][3] != 102)
		printf("[KO] multiply matrix 4X4 function\n");
	else if (can3.array[3][0] != 16 || can3.array[3][1] != 26 || can3.array[3][2] != 46 || can3.array[3][3] != 42)
		printf("[KO] multiply matrix 4X4 function\n");
	else
		printf("[OK] multiply matrix 4X4 function\n");
}

void	test_multiply_matrix_4X4_by_tuple(void)
{
	t_canva	can;
	t_tuple	*tup;
	t_tuple *tup2;

	can = create_canva(4, 4);
	can.array[0][0] = 1;
	can.array[0][1] = 2;
	can.array[0][2] = 3;
	can.array[0][3] = 4;
	can.array[1][0] = 2;
	can.array[1][1] = 4;
	can.array[1][2] = 4;
	can.array[1][3] = 2;
	can.array[2][0] = 8;
	can.array[2][1] = 6;
	can.array[2][2] = 4;
	can.array[2][3] = 1;
	can.array[3][0] = 0;
	can.array[3][1] = 0;
	can.array[3][2] = 0;
	can.array[3][3] = 1;

	tup = create_tuple(1, 2, 3, 1);
	tup2 = multiplying_matrix_tuple(&can, *tup);
	if (tup2->coor[0] != 18 || tup2->coor[1] != 24 || tup2->coor[2] != 33 || tup2->coor[3] != 1)
		printf("[KO] multiply matrix 4X4 by tuple function\n");
	else
		printf("[OK] multiply matrix 4X4 by tuple function\n");
}

void	transposing_matrix_4X4(void)
{
	t_canva	can;
	t_canva	can2;

	can = create_canva(4, 4);
	can.array[0][0] = 0;
	can.array[0][1] = 9;
	can.array[0][2] = 3;
	can.array[0][3] = 0;
	can.array[1][0] = 9;
	can.array[1][1] = 8;
	can.array[1][2] = 0;
	can.array[1][3] = 8;
	can.array[2][0] = 1;
	can.array[2][1] = 8;
	can.array[2][2] = 5;
	can.array[2][3] = 3;
	can.array[3][0] = 0;
	can.array[3][1] = 0;
	can.array[3][2] = 5;
	can.array[3][3] = 8;

	can2 = transpose_4X4_matrix(can);
	if (can2.array[0][0] != 0 || can2.array[0][1] != 9 || can2.array[0][2] != 1 || can2.array[0][3] != 0)
		printf("[KO] transpose matrix 4X4\n");
	else if (can2.array[1][0] != 9 || can2.array[1][1] != 8 || can2.array[1][2] != 8 || can2.array[1][3] != 0)
		printf("[KO] transpose matrix 4X4\n");
	else if (can2.array[2][0] != 3 || can2.array[2][1] != 0 || can2.array[2][2] != 5 || can2.array[2][3] != 5)
		printf("[KO] transpose matrix 4X4\n");
	else if (can2.array[3][0] != 0 || can2.array[3][1] != 8 || can2.array[3][2] != 3 || can2.array[3][3] != 8)
		printf("[KO] transpose matrix 4X4\n");
	else
		printf("[OK] transpose matrix 4X4\n");
}

void	test_determinant_2X2_matrix(void)
{
	t_canva	can;

	can = create_canva(2, 2);
	can.array[0][0] = 1;
	can.array[0][1] = 5;
	can.array[1][0] = -3;
	can.array[1][1] = 2;
	if (get_determinant_2X2_matrix(can) != 17)
		printf("[KO] determinant matrix 2X2 function\n");
	else
		printf("[OK] determinant matrix 2X2 function\n");
}

void	test_submatrix_of_3X3_matrix(void)
{
	t_canva	can;
	t_canva	can2;

	can = create_canva(3, 3);
	can.array[0][0] = 1;
	can.array[0][1] = 5;
	can.array[0][2] = 0;
	can.array[1][0] = -3;
	can.array[1][1] = 2;
	can.array[1][2] = 7;
	can.array[2][0] = 0;
	can.array[2][1] = 6;
	can.array[2][2] = -3;

	can2 = get_submatrix(can, 0, 2);
	if (can2.array[0][0] != -3 || can2.array[0][1] != 2 || can2.array[1][0] != 0 || can2.array[1][1] != 6)
		printf("[KO] submatrix of matrix 3X3 function\n");
	else
		printf("[OK] submatrix of matrix 3X3 function\n");
}

void	test_submatrix_of_4X4_matrix(void)
{
	t_canva	can;
	t_canva	can2;

	can = create_canva(4, 4);
	can.array[0][0] = -6;
	can.array[0][1] = 1;
	can.array[0][2] = 1;
	can.array[0][3] = 6;
	can.array[1][0] = -8;
	can.array[1][1] = 5;
	can.array[1][2] = 8;
	can.array[1][3] = 6;
	can.array[2][0] = -1;
	can.array[2][1] = 0;
	can.array[2][2] = 8;
	can.array[2][3] = 2;
	can.array[3][0] = -7;
	can.array[3][1] = 1;
	can.array[3][2] = -1;
	can.array[3][3] = 1;

	can2 = get_submatrix(can, 2, 1);
	if (can2.array[0][0] != -6 || can2.array[0][1] != 1 || can2.array[0][2] != 6)
		printf("[KO] submatrix of matrix 4x4 function\n");
	else if (can2.array[1][0] != -8 || can2.array[1][1] != 8 || can2.array[1][2] != 6)
		printf("[KO] submatrix of matrix 4x4 function\n");
	else if (can2.array[2][0] != -7 || can2.array[2][1] != -1 || can2.array[2][2] != 1)
		printf("[KO] submatrix of matrix 4x4 function\n");
	else
		printf("[OK] submatrix of matrix 4x4 function\n");
}

void	test_minor_3X3_matrix(void)
{
	t_canva	can;
	int 	minor;

	can = create_canva(3, 3);
	can.array[0][0] = 3;
	can.array[0][1] = 5;
	can.array[0][2] = 0;
	can.array[1][0] = 2;
	can.array[1][1] = -1;
	can.array[1][2] = -7;
	can.array[2][0] = 6;
	can.array[2][1] = -1;
	can.array[2][2] = 5;
	minor = get_minor_3X3_matrix(can, 1, 0);
	if (minor == 25)
		printf("[OK] minor 3X3 matrix\n");
	else
		printf("[KO] minor 3X3 matrix\n");
}

void	test_cofactor_3X3_matrix(void)
{
	t_canva	can;
	int 	minor;
	int		minor2;
	int		cofactor;
	int		cofactor2;

	can = create_canva(3, 3);
	can.array[0][0] = 3;
	can.array[0][1] = 5;
	can.array[0][2] = 0;
	can.array[1][0] = 2;
	can.array[1][1] = -1;
	can.array[1][2] = -7;
	can.array[2][0] = 6;
	can.array[2][1] = -1;
	can.array[2][2] = 5;
	minor = get_minor_3X3_matrix(can, 0, 0);
	minor2 = get_minor_3X3_matrix(can, 1, 0);
	cofactor = get_cofactor_3X3_matrix(can, 0, 0);
	cofactor2 = get_cofactor_3X3_matrix(can, 1, 0);
	if (minor != -12 || minor2 != 25 || cofactor != -12 || cofactor2 != -25)
		printf("[KO] cofactor 3X3 matrix\n");
	else
		printf("[OK] cofactor 3X3 matrix\n");
}
void	test_determinant_3X3_matrix(void)
{
	t_canva	can;
	int		cofactor;
	int		cofactor2;
	int		cofactor3;
	int		determinant;

	can = create_canva(3, 3);
	can.array[0][0] = 1;
	can.array[0][1] = 2;
	can.array[0][2] = 6;
	can.array[1][0] = -5;
	can.array[1][1] = 8;
	can.array[1][2] = -4;
	can.array[2][0] = 2;
	can.array[2][1] = 6;
	can.array[2][2] = 4;
	cofactor = get_cofactor_3X3_matrix(can, 0, 0);
	cofactor2 = get_cofactor_3X3_matrix(can, 0, 1);
	cofactor3 = get_cofactor_3X3_matrix(can, 0, 2);
	determinant = get_determinant_3X3_matrix(can, 2, 2);
	if (cofactor != 56 || cofactor2 != 12 || cofactor3 != -46 || determinant != -196)
		printf("[KO] determinant 3X3 matrix\n");
	else
		printf("[OK] determinant 3X3 matrix\n");
}

void	test_determinant_of_4X4_matrix(void)
{
	t_canva	can;
	int		cofactor;
	int		cofactor2;
	int		cofactor3;
	int		cofactor4;
	int		determinant;
	int		determinant2;

	can = create_canva(4, 4);
	can.array[0][0] = -2;
	can.array[0][1] = -8;
	can.array[0][2] = 3;
	can.array[0][3] = 5;
	can.array[1][0] = -3;
	can.array[1][1] = 1;
	can.array[1][2] = 7;
	can.array[1][3] = 3;
	can.array[2][0] = 1;
	can.array[2][1] = 2;
	can.array[2][2] = -9;
	can.array[2][3] = 6;
	can.array[3][0] = -6;
	can.array[3][1] = 7;
	can.array[3][2] = 7;
	can.array[3][3] = -9;

	cofactor = get_cofactor_4X4_matrix(can, 0, 0);
	cofactor2 = get_cofactor_4X4_matrix(can, 0, 1);
	cofactor3 = get_cofactor_4X4_matrix(can, 0, 2);
	cofactor4 = get_cofactor_4X4_matrix(can, 0, 3);
	determinant = get_determinant_4X4_matrix(can, 3);
	determinant2 = get_determinant_4X4_matrix(can, 2);
	if (cofactor != 690 || cofactor2 != 447 || cofactor3 != 210 || cofactor4 != 51)
		printf("[KO] determinant of matrix 4x4 function\n");
	else if (determinant != -4071 || determinant2 != -4071)
		printf("[KO] determinant of matrix 4x4 function\n");
	else
		printf("[OK] determinant of matrix 4x4 function\n");
}

void	test1_invert_4X4_matrix(void)
{
	t_canva	can;
	t_canva	inverse_mat;

	can = create_canva(4, 4);
	can.array[0][0] = -5.0;
	can.array[0][1] = 2.0;
	can.array[0][2] = 6.0;
	can.array[0][3] = -8.0;
	can.array[1][0] = 1.0;
	can.array[1][1] = -5.0;
	can.array[1][2] = 1.0;
	can.array[1][3] = 8.0;
	can.array[2][0] = 7.0;
	can.array[2][1] = 7.0;
	can.array[2][2] = -6.0;
	can.array[2][3] = -7.0;
	can.array[3][0] = 1.0;
	can.array[3][1] = -3.0;
	can.array[3][2] = 7.0;
	can.array[3][3] = 4.0;

	inverse_mat = inverse_matrix_4X4(can);
	if (inverse_mat.array[0][0] != 116.0/532.0 || inverse_mat.array[0][1] != 240/532.0)
		printf("1[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[0][2] != 128.0/532.0 || inverse_mat.array[0][3] != -24/532.0)
		printf("2[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[1][0] != -430.0/532.0 || inverse_mat.array[1][1] != -775.0/532.0)
		printf("3[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[1][2] != -236.0/532.0 || inverse_mat.array[1][3] != 277/532.0)
		printf("4[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[2][0] != -42.0/532.0 || inverse_mat.array[2][1] != -119.0/532.0)
		printf("5[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[2][2] != -28.0/532.0 || inverse_mat.array[2][3] != 105/532.0)
		printf("6[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[3][0] != -278.0/532.0 || inverse_mat.array[3][1] != -433.0/532.0)
		printf("7[KO] inverse matrix 4X4 test 1 function\n");
	else if (inverse_mat.array[3][2] != -160.0/532.0 || inverse_mat.array[3][3] != 163/532.0)
		printf("8[KO] inverse matrix 4X4 test 1 function\n");
	else
		printf("[OK] inverse matrix 4X4 test 1 function\n");
}

// void	test2_invert_4X4_matrix(void)
// {
// 	t_canva	can;
// 	t_canva	inverse_mat;

// 	can = create_canva(4, 4);
// 	can.array[0][0] = 8.0;
// 	can.array[0][1] = -5.0;
// 	can.array[0][2] = 9.0;
// 	can.array[0][3] = 2.0;
// 	can.array[1][0] = 7.0;
// 	can.array[1][1] = 5.0;
// 	can.array[1][2] = 6.0;
// 	can.array[1][3] = 1.0;
// 	can.array[2][0] = -6.0;
// 	can.array[2][1] = 0.0;
// 	can.array[2][2] = 9.0;
// 	can.array[2][3] = 6.0;
// 	can.array[3][0] = -3.0;
// 	can.array[3][1] = 0.0;
// 	can.array[3][2] = -9.0;
// 	can.array[3][3] = -4.0;

// 	inverse_mat = inverse_matrix_4X4(can);
// 	display_canva(&inverse_mat);
// 	printf("value : %f, test inequality : %d\n", inverse_mat.array[1][1], inverse_mat.array[1][1] == 0.123077/1.0);
// 	if (inverse_mat.array[0][0] != -0.153846 || inverse_mat.array[0][1] != -0.153846)
// 		printf("1[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[0][2] != -0.282051 || inverse_mat.array[0][3] != -0.538462)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[1][0] != -0.076923 || inverse_mat.array[1][1] != 0.123077)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[1][2] != 0.025641 || inverse_mat.array[1][3] != 0.030769)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[2][0] != 0.358974 || inverse_mat.array[2][1] != 0.358974)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[2][2] != 0.435897 || inverse_mat.array[2][3] != 0.923077)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[3][0] != -0.692308 || inverse_mat.array[3][1] != -0.692308)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else if (inverse_mat.array[3][2] != -0.769231 || inverse_mat.array[3][3] != -1.923077)
// 		printf("[KO] inverse matrix 4X4 test 2 function\n");
// 	else
// 		printf("[OK] inverse matrix 4X4 test 2 function\n");
// }

void	test_multiply_product_by_inverse(void)
{
	t_canva	can;
	t_canva	can2;
	t_canva can3;
	t_canva invert_can2;
	t_canva	can4;

	can = create_canva(4, 4);
	can.array[0][0] = 3.0;
	can.array[0][1] = -9.0;
	can.array[0][2] = 7.0;
	can.array[0][3] = 3.0;
	can.array[1][0] = 3.0;
	can.array[1][1] = -8.0;
	can.array[1][2] = 2.0;
	can.array[1][3] = -9.0;
	can.array[2][0] = -4.0;
	can.array[2][1] = 4.0;
	can.array[2][2] = 4.0;
	can.array[2][3] = 1.0;
	can.array[3][0] = -6.0;
	can.array[3][1] = -5.0;
	can.array[3][2] = -1.0;
	can.array[3][3] = 1.0;

	can2 = create_canva(4, 4);
	can2.array[0][0] = 8.0;
	can2.array[0][1] = 2.0;
	can2.array[0][2] = 2.0;
	can2.array[0][3] = 2.0;
	can2.array[1][0] = 3.0;
	can2.array[1][1] = -1.0;
	can2.array[1][2] = 7.0;
	can2.array[1][3] = 0.0;
	can2.array[2][0] = 7.0;
	can2.array[2][1] = 0.0;
	can2.array[2][2] = 5.0;
	can2.array[2][3] = 4.0;
	can2.array[3][0] = 6.0;
	can2.array[3][1] = -2.0;
	can2.array[3][2] = 0.0;
	can2.array[3][3] = 5.0;
	
	can3 = multiplying_4X4_matrix(&can, &can2);
	invert_can2 = inverse_matrix_4X4(can2);
	can4 = multiplying_4X4_matrix(&can3, &invert_can2);
	// display_canva(&can);
	// display_canva(&can4);
	if (compare_2Dmatrix(&can4, &can))
		printf("[OK] multiply a product by inverse function\n");
	else
		printf("[KO] multiply a product by inverse function\n");
}

