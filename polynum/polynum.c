#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 100
#define NUM_OF_OBJECT_MONOM 2
#define STRING_EOF "\0"
#define FLAG_TO_DEC_SORT 0

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
Monom* combinePowers(Monom* oldPolynom, int* size);
void printPolySum(Monom* poly1, int size1, Monom* poly2, int size2);
void printPolyMul(Monom* poly1, int size1, Monom* poly2, int size2);

void main() {
	Monom* polynom1, * polynom2;             // The input polynoms
	unsigned int polynom1Size, polynom2Size; // The size of each polynom

	printf("Please enter the first polynom:\n");
	polynom1 = getPolynom(&polynom1Size);   // get polynom 1

	printf("Please enter the second polynom:\n");
	polynom2 = getPolynom(&polynom2Size);   // get polynom 2

	printf("The multiplication of the polynoms is:\n"); // print the multiplication
	printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	printf("The sum of the polynoms is:\n"); // print the sum
	printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	free(polynom1); // releasing all memory allocations
	free(polynom2);
}

void printPolyMul(Monom* poly1, int size1, Monom* poly2, int size2) {
    int poly1Index = 0;
    int poly2Index = 0;
    Monom* polyMul;
    int polyMulIndex = 0;
    int maxSizeMul = 10;
    int i, j;
    polyMul = (Monom*)(malloc(sizeof(Monom) * maxSizeMul));
    if (!polyMul) {
        printf("MEMORY ERROR");
    }
    for ( i = 0; i < size1; i++)
    {
        for ( j = 0; j < size2; j++)
        {
            polyMul[polyMulIndex].power = poly2[j].power + poly1[i].power;
            polyMul[polyMulIndex].coefficient = poly2[j].coefficient * poly1[i].coefficient;
            polyMulIndex++;
            if (polyMulIndex == maxSizeMul) {
                maxSizeMul *= 2;
                polyMul = (Monom*)(realloc(polyMul, sizeof(Monom)*maxSizeMul));
            }
        }
    }
    mergeSort(polyMul, polyMulIndex, FLAG_TO_DEC_SORT);
    polyMul = combinePowers(polyMul, &polyMulIndex);
    printPolynom(polyMul, polyMulIndex);
    free(polyMul);
}

void printPolySum(Monom* poly1, int size1, Monom* poly2, int size2) {
    int poly1Index = 0;
    int poly2Index = 0;
    Monom* polySum;
    int polySumIndex = 0;
    polySum = (Monom*)(malloc(sizeof(Monom) * (size1 + size2)));
    while (poly1Index != size1 && poly2Index != size2)
    {
        if (poly1[poly1Index].power == poly2[poly2Index].power) {
            polySum[polySumIndex].power = poly1[poly1Index].power;
            polySum[polySumIndex].coefficient = poly1[poly1Index].coefficient + poly2[poly2Index].coefficient;
            poly1Index++;
            poly2Index++;
        }
        else {
            polySum[polySumIndex].power = poly1[poly1Index].power;
            polySum[polySumIndex].coefficient = poly1[poly1Index].coefficient;
            poly1Index++;
        }
        polySumIndex++;
    }
    while (poly1Index != size1)
    {
        polySum[polySumIndex].power = poly1[poly1Index].power;
        polySum[polySumIndex].coefficient = poly1[poly1Index].coefficient;
        poly1Index++;
        polySumIndex++;
    }
    while (poly2Index != size2)
    {
        polySum[polySumIndex].power = poly2[poly2Index].power;
        polySum[polySumIndex].coefficient = poly2[poly2Index].coefficient;
        poly2Index++;
        polySumIndex++;
    }
    mergeSort(polySum, polySumIndex, FLAG_TO_DEC_SORT);
    printPolynom(polySum, polySumIndex);
    free(polySum);
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

Monom* combinePowers(Monom* oldPolynom, int* size) {
    int i;
    int newPolyIndex = 0;
    int needTobeMoveOn = *size - 1;
    bool flagDuplicateCombine = false;
    Monom* newPolynom = (Monom*)(malloc(sizeof(Monom) * *size));
    if (!newPolynom) {
        printf("MEMORY ERROR");
    }
    if (*size == 1) {
        newPolynom[newPolyIndex].power = oldPolynom[0].power;
        newPolynom[newPolyIndex].coefficient = oldPolynom[0].coefficient;
        free(oldPolynom);
        return newPolynom;
    }
    for (i = 0; i < *size - 1; i++)
    {
        if (oldPolynom[i].power == oldPolynom[i + 1].power) {
            newPolynom[newPolyIndex].power = oldPolynom[i].power;
            newPolynom[newPolyIndex].coefficient = oldPolynom[i].coefficient + oldPolynom[i + 1].coefficient;
            i++;
            needTobeMoveOn--;
            while (oldPolynom[i].power == oldPolynom[i+1].power)
            {
                newPolynom[newPolyIndex].coefficient += oldPolynom[i+1].coefficient;
                i++;
                flagDuplicateCombine = true;
            }

        }
        else {
            newPolynom[newPolyIndex] = oldPolynom[i];
            if (i == *size - 2) {
                newPolyIndex++;
                newPolynom[newPolyIndex] = oldPolynom[i + 1];
            }
        }
        newPolyIndex++;
    }
    if (flagDuplicateCombine) {
        newPolynom[newPolyIndex] = oldPolynom[i];
        newPolyIndex++;
    }
    newPolynom = realloc(newPolynom, sizeof(Monom) * (newPolyIndex +1));
    *size = (newPolyIndex);
    if (!newPolynom) {
        printf("MEMORY ERROR");
    }
    free(oldPolynom);
    return newPolynom;
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
        token = strtok(NULL, specs);
        sscanf(token, "%d", &powerInput);
        if (coefficentInput != 0) {
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
    mergeSort(polynom, *size, FLAG_TO_DEC_SORT);
    polynom = combinePowers(polynom, size);
    return polynom;
}

void printPolynom(Monom* polyNom, int size) {
    int i;
    for (i = 0; i < size; i++)
    {
        switch (polyNom[i].power)
        {
        case 0:
             if (polyNom[i].coefficient != 0 ) {
                printf("%d", polyNom[i].coefficient < 0 ? polyNom[i].coefficient * -1 : polyNom[i].coefficient);
            }

            break;
        case 1:
            if (polyNom[i].coefficient == 1) {
                printf("X");
            } 
            if (i == 0) {
                printf("%dX", polyNom[i].coefficient);
            }
            else {
                printf("%dX", polyNom[i].coefficient < 0 && i != 0 ? polyNom[i].coefficient * -1 : polyNom[i].coefficient);
            }
                
            break;
        default:
            if (i == 0 && polyNom[i].coefficient < 0) {
                if (polyNom[i].coefficient == -1) {
                    printf("-X^%d", polyNom[i].power);
                } else
                printf("%dX^%d", polyNom[i].coefficient, polyNom[i].power);
            }
            else
            if (polyNom[i].coefficient == 1) {
                printf("X^%d", polyNom[i].power);
            }
            else
            printf("%dX^%d", polyNom[i].coefficient < 0 ? polyNom[i].coefficient * -1  : polyNom[i].coefficient, polyNom[i].power);
            break;
        }
        if (i != size - 1) {
            if(polyNom[i + 1].coefficient != 0)
            printf("%s", polyNom[i + 1].coefficient > 0 ? " + " : " - ");
        }

    }
}