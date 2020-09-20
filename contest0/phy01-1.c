#include <stdio.h>
#include <stdlib.h>


// uint16_t satsum(uint16_t x, uint16_t y);


// int main(int argc, char *argv[]) {
// 	int a, b;
// 	scanf("%d %d", &a, &b);
// 	printf("%d\n", satsum(a, b));
// }

uint16_t satsum(uint16_t x, uint16_t y) {
	if ((uint16_t)(x + y) < x) {
		return (uint16_t)(-1);
	}
	return x + y;
}