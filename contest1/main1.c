#include <stdio.h>
#include <stdlib.h>

int summ() {

}

int main() {
	int x0, N;
	int* x;
	scanf("%d%d", &x0, &N);
	x = malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i) scanf("%d", &x[i]);

	int sum = summ(x0, N, x);
	printf("%d\n", sum);
}