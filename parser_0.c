#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void remove_chars(char *, const char *);
void remove_char(char *, const char);
void remove_wspaces(char *);


/* Remove multiple chars (each treated as a single char) from input string */
void remove_chars(char *str, const char *rmvchars) {
    while (*rmvchars!='\0') {
    	remove_char(str, *rmvchars);
    	rmvchars++;
    }
}


/* Remove single char from input string */
void remove_char(char *str, const char rmvchar) {
    char *fw = str;
    while (*fw) {
        while(*fw==rmvchar){
			fw++;
        }
        *str = *fw;
		str++;
		fw++;
    }
    *str = '\0';
}


/* Remove whitespaces from input string */
void remove_wspaces(char *str) {
    remove_chars(str, " \t\n\v\f\r");
}


/* strstrtok gets a string pointer and and a string delimiter and returns delimited string as output */
/* and change input string pointer to point after delimited text. */
/* Example:     *str = "salambarali; delimiter="bar"; */
/*              ==> Output="salam"; *str = "ali";*/
char *strstrtok(char **pstr, const char *delimiter){
    char *pch1 = strstr(*pstr, delimiter);
    if (pch1!=NULL) {
        char *pch2;
        pch2 = *pstr;
        *pch1 = '\0';
        *pstr = pch1 + strlen(delimiter);
        return pch2;
    }
    else return *pstr;   /* If delimiter not found in input string => output is the same as input. */
}


/*
 * strstrtokmul takes an string and tokenize it by arbitrary number of delimiters (string type)
 */
char *strstrtokmul(char **pstr, ...) {
	va_list delimiters_list;
	va_start(delimiters_list, pstr); /* ?? pstr or **pstr ?? */
	
	char *delimiter;
	char *srchres;
	delimiter = va_arg(delimiters_list, char *);
	/* Last argument must be 0 */
	while (delimiter!=0) {
		srchres = strstrtok(pstr, delimiter);
		
		if (srchres!=*pstr) {
			return srchres;
		}
		delimiter = va_arg(delimiters_list, char *);
	}
	va_end(delimiters_list);
	return *pstr;
}


/*
 * A=B(C,D)
 * A=B(C)
 * A=B()
 * A=B
 * A()
 * A
 */

void parser(char **EX, char **A, char **B, char **C, char **D) {
    remove_wspaces(*EX);
    if (**EX!=0)  *A = strstrtokmul(EX, "=", "(", 0);
    else          *A = 0; *B=0; *C=0; *D=0; return;
    
    if (*EX!=NULL)  *B = strstrtokmul(EX, "(", 0);
    else            *B = 0;
    
    if (*EX!=NULL)  *C = strstrtokmul(EX, ",", ")", 0);
    else            *C = 0;
    
}


#define MAX_EX_LEN 64
int main(void) {

	char *EX = malloc(sizeof(char)*MAX_EX_LEN);
    char *EX_orig = EX;
    strcpy(EX, "");
    char *A, *B, *C, *D;
    //while (1) {
        //fgets(EX, MAX_EX_LEN, stdin);
        parser(&EX, &A, &B, &C, &D);
        printf("%s\n", A);
        printf("%s\n", B);
        printf("%s\n", C);
        printf("%s\n", D);
    //}
    

    free(EX_orig);


    return 0;
}
