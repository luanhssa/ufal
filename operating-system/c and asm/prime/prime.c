#include<stdio.h>
/*
int prime(int number) {
	if (number <= 1) {
		return 0; // zero and one are not prime
	}
	int i;
	for (i=2; i*i<=number; i++) {
		if (number % i == 0) {
			return 0;
		}
	}
	return 1;
}
*/
extern prime(int x);

int main() {
	int x = 5;

	x = prime(x);

	printf("%d\n", x);
}
