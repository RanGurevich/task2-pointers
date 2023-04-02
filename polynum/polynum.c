#define _CRT_SECURE_NO_WARNINGS
//#define SYSTEM_SPACE "   "
#define SYSTEM_SPACE " "
#define SYSTEM_SPACE_WITH_INT "   %d"
#define MAX_STRING_SIZE 100
#define NUM_OF_OBJECT_MONOM 2
#define STRING_EOF "\0"
#define END_INPUT_STRING "\n"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct monom {
	int coefficient; 
	int power;		
} Monom;

Monom* getPolynom(unsigned int* size);

void main() {
	Monom* polynom1, * polynom2;             // The input polynoms
	unsigned int polynom1Size, polynom2Size; // The size of each polynom

	printf("Please enter the first polynom:\n");
	polynom1 = getPolynom(&polynom1Size);   // get polynom 1

	//printf("Please enter the second polynom:\n");
	//polynom2 = getPolynom(&polynom2Size);   // get polynom 2

	//printf("The multiplication of the polynoms is:\n"); // print the multiplication
	//printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
	//printf("\n");

	//printf("The sum of the polynoms is:\n"); // print the sum
	//printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
	//printf("\n");

	//free(polynom1); // releasing all memory allocations
	//free(polynom2);
}
//int getPolyonomSize(char* inputString) {
//	int count = 0;
//	char steps[] = SYSTEM_SPACE;
//	char *inputToWorkOn = strtok(inputString, steps);
//	while (inputToWorkOn)
//	{
//		count++;
//		inputToWorkOn = strtok(inputToWorkOn, NULL);
//	}
//	return (count / NUM_OF_OBJECT_MONOM);
//
//}
//Monom* getPolynom(unsigned int* size) {
//	Monom* polynom;
//	char inputString[MAX_STRING_SIZE];
//	char *token;
//	int i;
//	int maxPolynomSize = 1;
//	char* specs = " \t\n";
//	bool inputFinished = false;
//	*size = 0;
//	polynom = (Monom*)malloc(sizeof(Monom) * maxPolynomSize);
//	if (!polynom) {
//		printf("MEMORY ERROR");
//	}
//	gets(inputString);
//	printf("%s", inputString);
//	token = strtok(inputString, specs);
//	while (token)
//	{
//		sscanf(token, "%d", &((polynom + *size)->coefficient));
//		printf("** %d **", ((polynom + *size)->coefficient));
//		token = strtok(NULL, specs);
//		printf("%s", inputString);
//		sscanf(token, "%d", &((polynom + *size)->power));
//		*size++;
//		if (*size == maxPolynomSize) {
//		maxPolynomSize *= 2;
//		polynom = realloc(polynom, maxPolynomSize * sizeof(Monom));
//		if (!polynom) {
//			printf("MEMORY ERROR");
//			}
//		}
//		token = strtok(NULL, SYSTEM_SPACE);
//	}
//	//while (!inputFinished)
//	//{
//	//	if (*size == maxPolynomSize) {
//	//		maxPolynomSize *= 2;
//	//		polynom = realloc(polynom, maxPolynomSize * sizeof(Monom));
//	//	}
//	//	(*size)++;  // increment size before the scanf calls
//	//	scanf("%d", &((polynom + *size - 1)->coefficient));
//	//	scanf("%d", &((polynom + *size - 1)->power));
//	//	if (getchar() == END_INPUT_STRING) {
//	//		inputFinished = true;
//	//	}
//	//}
//
//	return polynom;
//}



Monom* getPolynom(unsigned int* size) {
    Monom* polynom;
    char inputString[MAX_STRING_SIZE];
    char* token;
    int i;
    int maxPolynomSize = 1;
    char* specs = " \t\n";
    bool inputFinished = false;
    *size = 0;
    polynom = (Monom*)malloc(sizeof(Monom) * maxPolynomSize);
    if (!polynom) {
        printf("MEMORY ERROR");
    }
    gets(inputString);
    token = strtok(inputString, specs);
    while (token)
    {
        sscanf(token, "%d", &((polynom + *size)->coefficient));
        token = strtok(NULL, specs);
        sscanf(token, "%d", &((polynom + *size)->power));
        *size += 1;
        if (*size == maxPolynomSize) {
            maxPolynomSize *= 2;
            polynom = realloc(polynom, maxPolynomSize * sizeof(Monom));
            if (!polynom) {
                printf("MEMORY ERROR");
            }
        }
        token = strtok(NULL, specs);
    }

    return polynom;
}