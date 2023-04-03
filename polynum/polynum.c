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
void printPolynom(Monom* polyNom, int size);
void mergeSort(Monom* arr, int size, int flagPosition);
void merge(Monom* arr1, int sizeArr1, Monom* arr2, int sizeArr2, Monom* resArr, int flagPosition);
void copyArr(Monom dest[], Monom src[], int size);

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

void mergeSort(Monom* arr, int size, int flagPosition)
{
    // the function implement merge sort, with option to smaller number
    // to bigger number and from bigger number to smaller using the flag position
    Monom* tmpArr = NULL;
    if (size <= 1)
        return;

    mergeSort(arr, size / 2, flagPosition);
    mergeSort(arr + size / 2, size - size / 2, flagPosition);

    tmpArr = (Monom*)malloc(size * sizeof(Monom));
    if (tmpArr)
    {
        merge(arr, size / 2, arr + size / 2, size - size / 2, tmpArr, flagPosition);
        copyArr(arr, tmpArr, size); // copy values from tmpArr to arr
        free(tmpArr);
    }
    else
    {
        printf("Memory allocation failure!!!\n");
        exit(1);	// end program immediately with code 1 (indicating an error)
    }
}

void merge(Monom* arr1, int sizeArr1, Monom* arr2, int sizeArr2, Monom* resArr, int flagPosition)
{
    // the function merge 2 arrays, if the flag position is positive the merge will be from the smaller number to bigger
    int indexArr1, indexArr2, indexArrRes;
    indexArr1 = indexArr2 = indexArrRes = 0;

    while ((indexArr1 < sizeArr1) && (indexArr2 < sizeArr2)) {
        if (flagPosition ? arr1[indexArr1].power <= arr2[indexArr2].power : arr1[indexArr1].power >= arr2[indexArr2].power) {
            resArr[indexArrRes] = arr1[indexArr1];
            indexArr1++;
        }
        else {
            resArr[indexArrRes] = arr2[indexArr2];
            indexArr2++;
        }
        indexArrRes++;
    }

    while (indexArr1 < sizeArr1) {
        resArr[indexArrRes] = arr1[indexArr1];
        indexArr1++;
        indexArrRes++;
    }
    while (indexArr2 < sizeArr2) {
        resArr[indexArrRes] = arr2[indexArr2];
        indexArr2++;
        indexArrRes++;
    }
}


void copyArr(Monom dest[], Monom src[], int size)
{
    // the function get array from dest and copy it to the src
    int i;

    for (i = 0; i < size; i++)
        dest[i] = src[i];
}


Monom* getPolynom(unsigned int* size) {
    Monom* polynom;
    char inputString[MAX_STRING_SIZE];
    char* token;
    int i;
    int powerInput, coefficentInput;
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
        sscanf(token, "%d", &coefficentInput);
       // sscanf(token, "%d", &((polynom + *size)->coefficient));
        token = strtok(NULL, specs);
        sscanf(token, "%d", &powerInput);
       // sscanf(token, "%d", &((polynom + *size)->power));
        if (powerInput != 0 && coefficentInput != 0) {
            (polynom + *size)->coefficient = coefficentInput;
            (polynom + *size)->power = powerInput;
            *size += 1;
            if (*size == maxPolynomSize) {
                maxPolynomSize *= 2;
                polynom = realloc(polynom, maxPolynomSize * sizeof(Monom));
                if (!polynom) {
                    printf("MEMORY ERROR");
                }
            }
        }

        token = strtok(NULL, specs);
    }
    mergeSort(polynom, *size, 0);
    printPolynom(polynom, *size);
    return polynom;
}

void printPolynom(Monom* polyNom, int size) {
    int i;
    for ( i = 0; i < size; i++)
    {
        printf("%dX^%d", polyNom[i].coefficient, polyNom[i].power);
        if (i != size - 1 && polyNom[i + 1].coefficient > 0) {
            printf("%c", '+');
        }
    }
}