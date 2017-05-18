/*
수치해석 과제1

상하행렬분해 부분 피봇팅 가우스소거법을 사용하여
PAx = Pc = d의 변수벡터 x를 구하는 프로그램

상하행렬분해
LUx = c,
Ly = c,
Ux = y
*/

#include <stdio.h>
#include <Windows.h>

// 행렬 size
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
	// 디폴트 행렬
	double A[size][size] = {
		{ -1, 1, 2 },
		{ 1, 2, -1 },
		{ -2, -2, 2 }
	};
	// 치환 행렬
	double P[size][size];
	double L[size][size];
	double U[size][size];

	// 벡터 변수
	double x[size];
	double y[size];
	double d[size];
	double c[size] = { 7, 2, 0 };		// 디폴트 값

	int i, j, k;
	int pivot_row;

	// 초기화
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == j) {
				// 주대각선에서 L은 1로, P는 1로 초기화
				L[i][j] = 1;
				P[i][j] = 1;
			}
			else if (j > i) {
				// 상 행렬을 A원소로 초기화, P는 0
				L[i][j] = 0;
				P[i][j] = 0;
			}
			else {
				// 모두 0으로 초기화
				L[i][j] = 0;
				P[i][j] = 0;
			}
		}	// y 반복문 종료

		// 변수벡터 초기화
		x[i] = 0;
		y[i] = 0;
		d[i] = 0;
		
	}	// 초기화 종료

	// L 행렬, U행렬 계산, 부분 피봇팅 추가
	for (k = 0; k < size - 1; k++) {	// size가 3이라면, 2단계만 진행 
										// 왜냐하면, 마지막 열의 승수는 구하지 않기 때문

		// 절댓값이 가장 큰 행과 현재 행의 치환 행렬 P를 구하고,
		// 두 행을 자리바꿈
		pivot_row = k;
		for (i = k; i < size; i++) {
			if (AbsoluteValue(A[pivot_row][k]) < AbsoluteValue(A[i][k]))
				pivot_row = i;
		}

		if (k != pivot_row) {
			// 치환 행렬 계산
			for (j = 0; j < size; j++) {
				Swap_double(&P[k][j], &P[pivot_row][j]);
			}

			// A 배열 행 자리바꿈
			for (j = 0; j < size; j++) {
				Swap_double(&A[k][j], &A[pivot_row][j]);
			}
			// L행렬 피봇팅
			for (j = 0; j < k; j++) {
				Swap_double(&L[k][j], &L[pivot_row][j]);
			}
		}

		// 행에 대한 반복
		for (i = k; i < size; i++) {
			if (i == k) continue;	// 피봇 행은 승수를 구하지 않음

									// 승수 계산, L행렬 대입
			L[i][k] = A[i][k] / A[k][k];

			// 열에 대한 반복
			for (j = k; j < size; j++) {
				// 피봇 행으로 다른 행 빼기
				A[i][j] = A[i][j] - (L[i][k] * A[k][j]);

			}	// 열 반복 종료

		}	// 행 반복 종료

		// U행렬 초기화
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				U[i][j] = A[i][j];
			}
		}

	}	// 가우스 소거법 종료

	// d벡터 구하기,  d = Pc
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			d[i] += (P[i][j] * c[j]);
		}
	}

	// 디버그 코드
	printf("A");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// 디버그 코드
	printf("L");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", L[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// 디버그 코드
	printf("U");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("	%.2lf", U[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Ly = d, y벡터 해 구하기
	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			d[i] -= (y[j] * L[i][j]);
		}
		j = i;
		y[i] = d[i] / L[i][j];
	}

	// 디버깅 코드
	printf("y\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", y[i]);
	}
	printf("\n\n");

	// Ux = y, x벡터 해 구하기
	for (i = size - 1; i >= 0; i--) {
		for (j = size - 1; j > i; j--) {
			y[i] -= (x[j] * U[i][j]);
		}
		j = i;
		x[i] = y[i] / U[i][j];
	}

	// 디버깅 코드
	printf("x\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", x[i]);
	}
	printf("\n\n");
}