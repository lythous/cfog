#include <stdio.h>

double cube(double);
double inv(double);

// Define a type for a pointer to a function which gets a double and returns a double too
typedef double (*fp_double_in_double_out)(double);


double fog(fp_double_in_double_out, fp_double_in_double_out, double);

// This function gets two function pointer and an input value and returns a return value
double fog(fp_double_in_double_out f, fp_double_in_double_out g, double x) {
	double y = (*g)(x);
	double z = (*f)(y);
	return z;
}


// Is it possible to define a function which only rakes two function pointer and returns 
// a function pointer of fog?

// Function simple wrapper
fp_double_in_double_out func_wrapper(fp_double_in_double_out f) {
    printf("running f\n");
    return f;
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
	printf("%f\n", (*func_wrapper(cube))(5));
	printf("%f\n", (*func_wrapper(inv))(5));
	return 0;
}
