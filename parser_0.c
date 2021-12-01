#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_spaces(char* str) {
    char *fw = str;
    while (*fw) {
        while(*fw==' '){
			fw++;
        }
        *str = *fw;
		str++;
		fw++;
    }
}

void test(void) {
	char *ex = malloc(sizeof(char)*64);
	strcpy(ex, "sa = fun(x1, x2)");
	char *pch;
	pch = strtok(ex, ";");
	if (pch==NULL) printf("Not Found!\n");
	else printf("Found!\n");
	
	printf("%s\n", pch);
}

void parser(char *ex, char *var, char *func, char *param1, char *param2) {
	char *pch;
	pch = strtok(ex, "=");
	strcpy(var, pch);
	if (strcmp(var, ex)) strcpy(var, "");
	
	pch = strtok(NULL, "(");
	printf("%s\n", pch);
	//strcpy(func, pch);	
	
	//pch = strtok(NULL, ",");
	//strcpy(param1, pch);
	
	//pch = strtok(NULL, ")");
	//strcpy(param2, pch);
}

#define MAX_EX_LEN 64
int main(void) {

	//test();
	char *ex = malloc(sizeof(char)*MAX_EX_LEN);
	char *var = malloc(sizeof(char)*MAX_EX_LEN);
	char *func = malloc(sizeof(char)*MAX_EX_LEN);
	char *param1 = malloc(sizeof(char)*MAX_EX_LEN);
	char *param2 = malloc(sizeof(char)*MAX_EX_LEN);
	
	while (1) {
		//printf(">>");
		
		fgets(ex, MAX_EX_LEN, stdin);
		//strcpy(ex, "func(param1, param2)");
		//printf("%s\n", ex);
		parser(ex, var, func, param1, param2);
		printf("%s, %s, %s, %s\n", var, func, param1, param2);
		//getchar();

	}
	free(ex);
	free(func);
	free(param1);
	free(param2);


    return 0;
}
