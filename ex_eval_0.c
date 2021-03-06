# include <stdio.h>
# include <stdlib.h>
# include <math.h>

/* ALL INPUT AND OUTPUT NUMBERS FOR ALL FUNCTIONS ARE OF DOUBLE TYPE. */


/* 
 * Each function node contain output and inputs and operation function pointer.
 * Variables for simplicity has been defined as function node; If both of input
 * pointers are NULL then the node is a variable. Otherwise its a single or double 
 * input input function.
 */
typedef struct function_node {
	void					*func;
	struct function_node	*in_1;
	struct function_node	*in_2;
	double					out;
	char					*name;
} fnode;

typedef struct fn_identifier_ {
	fnode	*fn;
	char	*identifier;
} fn_identifier;


/* Define types for function pointers */
typedef double (*func_ptr_1in)(double);			// 1 Input; 1 output;
typedef double (*func_ptr_2in)(double, double);	// 2 Input; 1 output;


/* Function Declarations */
void test(void);
double eval(fnode*);
double mul(double, double);
void fnode_set_val(fnode*, double);
void fnode_init_as_var(fnode*, double, char*);
void fnode_init_as_func_1in(fnode*, func_ptr_1in, fnode*, double);
fnode *get_fn_by_name(fnode *, int, char *);


/* Evaluate a function node hierarchically (from that node to the lower nodes) */
double eval(fnode *fn) {
	/* Node Type: Function [2 Input; 1 output] */
	if ((fn->in_1) && (fn->in_2)) {
		func_ptr_2in func = (func_ptr_2in)fn->func;
		eval(fn->in_1);
		eval(fn->in_2);
		fn->out = func(fn->in_1->out, fn->in_2->out);
	}
	/* Node Type: Function [1 Input; 1 output] */
	if ((fn->in_1) && !(fn->in_2)) {
		func_ptr_1in func = (func_ptr_1in)fn->func;
		eval(fn->in_1);
		fn->out = func(fn->in_1->out);
	}
	/* Node Type: Variable */
	if (!(fn->in_1) && !(fn->in_2)) {
	}
	return fn->out;
}


/* Evaluate a function node without evaluating lower nodes */
double shallow_eval(fnode *fn) {
	if ((fn->in_1) && (fn->in_2)) {
		func_ptr_2in func = (func_ptr_2in)fn->func;
		fn->out = func(fn->in_1->out, fn->in_2->out);
	}
	if ((fn->in_1) && !(fn->in_2)) {
		func_ptr_1in func = (func_ptr_1in)fn->func;
		fn->out = func(fn->in_1->out);
	}
	return fn->out;
}


double mul(double x, double y) {
	return x*y;
}


/*
 * Some functions to initialize different types of function nodes and improve readability 
 */
void fnode_set_val(fnode *fn, double value) {
	fn->out = value;
}

void fnode_init_as_var(fnode *fn, double init_value, char *name) {
	fnode_set_val(fn, init_value);
	fn->name = name;
	fn->in_1 = NULL;
	fn->in_2 = NULL;	
}

void fnode_init_as_func_1in(fnode *fn, func_ptr_1in func, fnode *in_fn, double init_value) {
	fn->func = func;
	fn->out = init_value;
	fn->in_1 = in_fn;
	fn->in_2 = NULL;	
}

void fnode_init_as_func_2in(fnode *fn, func_ptr_2in func, fnode *in1_fn, fnode *in2_fn, double init_value) {
	fn->func = func;
	fn->out = init_value;
	fn->in_1 = in1_fn;
	fn->in_2 = in2_fn;	
}


/* Get a pointer to a function node by its name */
fnode *get_fn_by_name(fnode *fn_array, int fn_size, char *name) {
	for (int i=0; i<fn_size; i++) {
		if (fn_array[i].name == name)
			return &fn_array[i];
	}
	return NULL;
}

void test(void) {
	fnode *fn_array = malloc(4*sizeof(fnode));
	int fn_size = 4;
	if (fn_array) {
		fnode_init_as_var(&fn_array[0], 0.5, "x1");
		fnode_init_as_var(&fn_array[1], 3.1415, "x2");
		fnode_init_as_func_2in(&fn_array[2], mul, &fn_array[0], &fn_array[1], 0);
		fnode_init_as_func_1in(&fn_array[3], sin, &fn_array[2], 0);	
		printf("%f\n", eval(&fn_array[3]));
		get_fn_by_name(fn_array, 4, "x2")->out = 3;
		printf("%f\n", eval(&fn_array[3]));
	}

	free(fn_array);
}


int main(void) {
	printf("Salam\n");
	test();
	return 0;
}
