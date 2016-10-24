#include<stdio.h>
int f(int x) {
	printf("%d\n", x);
	x = 100;
	return x;
}

int main(){
	int x = 10;
	x = f(x);
	printf("%d\n", x);
}
