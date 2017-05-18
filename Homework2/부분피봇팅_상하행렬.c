/*
��ġ�ؼ� ����1

������ĺ��� �κ� �Ǻ��� ���콺�ҰŹ��� ����Ͽ�
PAx = Pc = d�� �������� x�� ���ϴ� ���α׷�

������ĺ���
LUx = c,
Ly = c,
Ux = y
*/

#include <stdio.h>
#include <Windows.h>

// ��� size
#define size 3

void Swap_double(double *px, double *py) 
{
	double temp = *px;

	*px = *py;
	*py = temp;
}
double AbsoluteValue(double a) {
	return (a >= 0 ? a : -a);
}

int main()
{
	// ����Ʈ ���
	double A[size][size] = {
		{ -1, 1, 2 },
		{ 1, 2, -1 },
		{ -2, -2, 2 }
	};
	// ġȯ ���
	double P[size][size];
	double L[size][size];
	double U[size][size];

	// ���� ����
	double x[size];
	double y[size];
	double d[size];
	double c[size] = { 7, 2, 0 };		// ����Ʈ ��

	int i, j, k;
	int pivot_row;

	// �ʱ�ȭ
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == j) {
				// �ִ밢������ L�� 1��, P�� 1�� �ʱ�ȭ
				L[i][j] = 1;
				P[i][j] = 1;
			}
			else if (j > i) {
				// �� ����� A���ҷ� �ʱ�ȭ, P�� 0
				L[i][j] = 0;
				P[i][j] = 0;
			}
			else {
				// ��� 0���� �ʱ�ȭ
				L[i][j] = 0;
				P[i][j] = 0;
			}
		}	// y �ݺ��� ����

		// �������� �ʱ�ȭ
		x[i] = 0;
		y[i] = 0;
		d[i] = 0;
		
	}	// �ʱ�ȭ ����

	// L ���, U��� ���, �κ� �Ǻ��� �߰�
	for (k = 0; k < size - 1; k++) {	// size�� 3�̶��, 2�ܰ踸 ���� 
										// �ֳ��ϸ�, ������ ���� �¼��� ������ �ʱ� ����

		// ������ ���� ū ��� ���� ���� ġȯ ��� P�� ���ϰ�,
		// �� ���� �ڸ��ٲ�
		pivot_row = k;
		for (i = k; i < size; i++) {
			if (AbsoluteValue(A[pivot_row][k]) < AbsoluteValue(A[i][k]))
				pivot_row = i;
		}

		if (k != pivot_row) {
			// ġȯ ��� ���
			for (j = 0; j < size; j++) {
				Swap_double(&P[k][j], &P[pivot_row][j]);
			}

			// A �迭 �� �ڸ��ٲ�
			for (j = 0; j < size; j++) {
				Swap_double(&A[k][j], &A[pivot_row][j]);
			}
			// L��� �Ǻ���
			for (j = 0; j < k; j++) {
				Swap_double(&L[k][j], &L[pivot_row][j]);
			}
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

			}	// �� �ݺ� ����

		}	// �� �ݺ� ����

		// U��� �ʱ�ȭ
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				U[i][j] = A[i][j];
			}
		}

	}	// ���콺 �ҰŹ� ����

	// d���� ���ϱ�,  d = Pc
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			d[i] += (P[i][j] * c[j]);
		}
	}

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

	// Ly = d, y���� �� ���ϱ�
	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			d[i] -= (y[j] * L[i][j]);
		}
		j = i;
		y[i] = d[i] / L[i][j];
	}

	// ����� �ڵ�
	printf("y\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", y[i]);
	}
	printf("\n\n");

	// Ux = y, x���� �� ���ϱ�
	for (i = size - 1; i >= 0; i--) {
		for (j = size - 1; j > i; j--) {
			y[i] -= (x[j] * U[i][j]);
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