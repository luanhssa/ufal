#include<stdio.h>

/*
int fat(int x) {
	int fat;
	for(fat = 1; x > 1; x = x - 1) {
		fat = fat * x;
	}
	return fat;
}
*/
extern fat(int x);

int main() {
	int x = 7;

	x = fat(x);

	printf("%d\n", x);
}
