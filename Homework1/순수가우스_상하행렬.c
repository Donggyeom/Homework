/*
수치해석 과제1

 상하행렬분해 가우스소거법을 사용하여
 Ax = c의 변수벡터 x를 구하는 프로그램

 상하행렬분해
   LUx = c,
   Ly = c,
   Ux = y
*/

#include <stdio.h>
#include <Windows.h>

// 행렬 size
#define size 3

int main()
{
	// 디폴트 행렬
	double A[size][size] = {
		{-2, 1, 0},
		{1, 0, 1},
		{0, -1, 2}
	};
	double L[size][size];
	double U[size][size];

	// 벡터 변수
	double x[size];
	double y[size];
	double c[size] = { 2, 3, 1 };		// 디폴트 값

	int i, j, k;
									
	// 초기화
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == j) {
				// 주대각선에서 L은 1로, U는 A원소로 초기화
				L[i][j] = 1;
				U[i][j] = A[i][j];
			}
			else if (j > i) {
				L[i][j] = 0;
				U[i][j] = A[i][j];
			}
			else {
				// 모두 0으로 초기화
				L[i][j] = 0;
				U[i][j] = 0;
			}
		}

		// 변수벡터 초기화
		x[i] = 0;
		y[i] = 0;
	}

	// L 행렬, U행렬 계산
	for (k = 0; k < size - 1; k++) {	// size가 3이라면, 2단계만 진행 
										// 왜냐하면, 마지막 열의 승수는 구하지 않기 때문
		// 피봇 원소가 0이라면 순수 가우스 소거법을 
		// 수행할 수 없으므로, 프로그램을 종료한다.
		if (A[k][k] == 0) {
			printf("%.2lf행 %.2lf열 피봇 원소가 0이므로, \
						순수 가우스 소거법을 적용할 수 없습니다.\n", i + 1, j + 1);
			system("pause");
			return 0;
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

				// U행렬 대입
				if (j >= i)
					U[i][j] = A[i][j];
		
			}	// 열 반복 종료

		}	// 행 반복 종료

	}	// 가우스 소거법 종료
	
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

	// Ly = c, y벡터 해 구하기
	for (i = 0; i < size; i++) {
		for (j = 0; j < i; j++) {
			c[i] -= (y[j] * L[i][j]);		// !! c값 수정됨
		}
		j = i;
		y[i] = c[i] / L[i][j];
	}

	// 디버깅 코드
	printf("y\n");
	for (i = 0; i < size; i++) {
		printf("%.2lf ", y[i]);
	}
	printf("\n\n");

	// Ux = y, x벡터 해 구하기
	for (i = size - 1; i >= 0;i--){
		for (j = size - 1; j > i; j--) {
			y[i] -= (x[j] * U[i][j]);		// !! y값 수정됨
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