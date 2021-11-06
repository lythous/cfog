// Modified Vesin
#include <stdio.h>

double cube(double);
double inv(double);
double fog(double (*)(double), double (*)(double), double);

double fog(double (*f)(double), double (*g)(double), double x) {
	double y = (*g)(x);
	double z = (*f)(y);
	return z;
}

double cube(double x) {
	return x*x*x;
}

double inv(double x) {
	return 1/x;
}

int main(void) {
	printf("Salam\n");
	printf("%f\n", cube(inv(0.5)));
	printf("%f\n", fog(cube, inv, 0.5));
	return 0;
}