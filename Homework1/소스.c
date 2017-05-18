/*
��ġ�ؼ� ����1

 ������ĺ��� ���콺�ҰŹ��� ����Ͽ�
 Ax = c�� �������� x�� ���ϴ� ���α׷�

 ������ĺ���
   LUx = c,
   Ly = c,
   Ux = y
*/

#include <stdio.h>
#include <Windows.h>

// ��� size
#define size 3

int main()
{
	// ����Ʈ ���
	double A[size][size] = {
		{-2, 1, 0},
		{1, 0, 1},
		{0, -1, 2}
	};
	double L[size][size];
	double U[size][size];

	// ���� ����
	double x[size];
	double y[size];
	double c[size] = { 2, 3, 1 };		// ����Ʈ ��

	int i, j, k;
									
	// �ʱ�ȭ
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == j) {
				// �ִ밢������ L�� 1��, U�� A���ҷ� �ʱ�ȭ
				L[i][j] = 1;
				U[i][j] = A[i][j];
			}
			else if (j > i) {
				L[i][j] = 0;
				U[i][j] = A[i][j];
			}
			else {
				// ��� 0���� �ʱ�ȭ
				L[i][j] = 0;
				U[i][j] = 0;
			}
		}

		// �������� �ʱ�ȭ
		x[i] = 0;
		y[i] = 0;
	}

	// L ���, U��� ���
	for (k = 0; k < size - 1; k++) {	// size�� 3�̶��, 2�ܰ踸 ���� 
										// �ֳ��ϸ�, ������ ���� �¼��� ������ �ʱ� ����
		// �Ǻ� ���Ұ� 0�̶�� ���� ���콺 �ҰŹ��� 
		// ������ �� �����Ƿ�, ���α׷��� �����Ѵ�.
		if (A[k][k] == 0) {
			printf("%.2lf�� %.2lf�� �Ǻ� ���Ұ� 0�̹Ƿ�, \
						���� ���콺 �ҰŹ��� ������ �� �����ϴ�.\n", i + 1, j + 1);
			system("pause");
			return 0;
		}
		// �࿡ ���� �ݺ�
		for (i = k; i < size; i++) {
			if (i == k) continue;	// �Ǻ� ���� �¼��� ������ ����
			
			// �¼� ���, L��� ����
			L[i][k] = A[i][k] / A[k][k];

			// ���� ���� �ݺ�
			for (j = k; j < size; j++) {
				// �Ǻ� ������ �ٸ� �� ����
				A[i][j] = A[i][j] - (L[i][k] * A[k][j]);

				// U��� ����
				if (j >= i)
					U[i][j] = A[i][j];
		
			}	// �� �ݺ� ����

		}	// �� �ݺ� ����

	}	// ���콺 �ҰŹ� ����
	
	// ����� �ڵ�
	printf("A");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	// ����� �ڵ�
	printf("L");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", L[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	// ����� �ڵ�
	printf("U");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", U[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Ly = c, y���� �� ���ϱ�
	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			c[i] -= (y[j] * L[i][j]);		// !! c�� ������
		}
		j = i;
		y[i] = c[i] / L[i][j];
	}

	// ����� �ڵ�
	printf("y\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", y[i]);
	}
	printf("\n\n");

	// Ux = y, x���� �� ���ϱ�
	for (i = size - 1; i >= 0;i--){
		for (j = size - 1; j > i; j--) {
			y[i] -= (x[j] * U[i][j]);		// !! y�� ������
		}
		j = i;
		x[i] = y[i] / U[i][j];
	}	

	// ����� �ڵ�
	printf("x\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", x[i]);
	}
	printf("\n\n");
}