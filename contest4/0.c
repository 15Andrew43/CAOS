#include <stdio.h>
#include <stdlib.h>

extern void summ(int N, const int *A, const int *B, int *R);

int main() {
	int N = 5;
	int* R = malloc(N * sizeof(int));
	int* A = malloc(N * sizeof(int));
	int* B = malloc(N * sizeof(int));
	
	A[0] = 1;
	A[1] = 2;
	A[2] = 3;
	A[3] = 4;
	A[4] = 5;

	B[0] = 1;
    B[1] = 2;
    B[2] = 3;
    B[3] = 4;
    B[4] = 5;

	summ(N, A, B, R);

	for (int i = 0; i < N; ++i) {
		printf("%d ", R[i]);
	}

	free(R);
	free(A);
	free(B);


	return 0;
}
