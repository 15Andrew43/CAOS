#include <stdio.h>
#include <stdlib.h>

enum {
	BASE = 27
};

int main(int argc, char *argv[]) {
	double x;
	int y;
	int z;
	scanf("%lf %x", &x, &y);
	z = strtol(argv[1], NULL, BASE);
	double result = x + y + z;
	printf("%.3f\n", result);
}