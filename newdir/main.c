#include <stdio.h>
#include "testlib.h"

int main()
{

	int x, y;

	printf("input value : ");
	scanf("%d %d", &x, &y);

	printf("Add : %d + %d = %d\n", x, y, Add(x, y));
	printf("Sub : %d - %d = %d\n", x, y, Sub(x, y));
	printf("Mul : %d * %d = %d\n", x, y, Mul(x, y));
	printf("Div : %d / %d = %d\n", x, y, Div(x, y));
	
	return 0;

}

