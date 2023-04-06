#define _CRT_SECURE_NO_WARNINGS
#define FLAG_TO_DEC_SORT 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char** getStrArrayInput(unsigned int* arrSize);
char** setPtrToCharsArray(char** str_array);
int getSizeOfPointerArray(char** arr);
void mergeSort(char** arr, int size, int flagPosition);
void merge(char** arr1, int sizeArr1, char** arr2, int sizeArr2, char** resArr, int flagPosition);
void copyArr(char** dest, char** src, int size);
unsigned int RemoveFromStrArray(char*** str_array, unsigned  int  str_array_size, char** ptr_to_chars_array);
int removePointerFromStringArray(char** stringArray, unsigned int stringArraySize, char* pointToRemove);
void searchInStringAndRemove(char* string, char* pointerToRemove);
void printArray(char** arr, unsigned int size);
void freeArray(char** arr, int size);

char** setPtrToCharsArray(char** str_array)
{
    char** res;
    int size, i;
    int str_array_row, str_array_col;

    scanf("%d", &size); // Get number of ptrs
    res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end

    if (res == NULL) {
        exit(1);
    }
    for (i = 0; i < size; i++)
    {
        scanf("%d", &str_array_row);
        scanf("%d", &str_array_col);
        res[i] = str_array[str_array_row] + str_array_col;
    }
    res[size] = NULL; // Set the last one to NULL
    return res;
}



int main()

{
    char** str_array;
    unsigned int str_array_size;
    char** ptr_to_chars_array;
    unsigned int res;


    str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)
    ptr_to_chars_array = setPtrToCharsArray(str_array);


    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);
    printArray(str_array, str_array_size - res);
   	// Free memory
   	freeArray(str_array, str_array_size - res);
    free(ptr_to_chars_array);
}
void freeArray(char** arr, int size) {
    int i;
    for ( i = 0; i < size; i++)
    {
        free(arr[i]);
    }
}
void printArray(char** arr, unsigned int size) {
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%s\n", arr[i]);
    }
}
unsigned int RemoveFromStrArray(char*** str_array, unsigned  int  str_array_size, char** ptr_to_chars_array) {
    int countRemoved = 0;
    int i;
    int sizeOfPointerArray = getSizeOfPointerArray(ptr_to_chars_array);
    mergeSort(ptr_to_chars_array, sizeOfPointerArray, FLAG_TO_DEC_SORT);
    for (i = 0; i < sizeOfPointerArray; i++)
    {
        countRemoved += removePointerFromStringArray(*str_array, str_array_size, *(ptr_to_chars_array + i));
    }
    return countRemoved;
}

int removePointerFromStringArray(char** stringArray, unsigned int stringArraySize, char* pointToRemove) {
    int i, j;
    int itemRemoved = 0;

    for (i = 0; i < stringArraySize; i++)
    {
        if (strlen(stringArray[i]) == 0) {
            // in case the string came already empty and just need to be removed, we will decrease the counter and then in the for loop the
            // the change will be return to 0
            itemRemoved--;
        }
        searchInStringAndRemove(stringArray[i], pointToRemove);
        if (strlen(stringArray[i]) == 0) {
            itemRemoved++;
            for (j = i; j < stringArraySize - 1; j++)
            {
                stringArray[j] = stringArray[j + 1];
            }
        }
    }
    return itemRemoved;
}

void searchInStringAndRemove(char* string, char* pointerToRemove) {
    int i = 0;
    int j;
    int stringSize = strlen(string);
    for (i = 0; i < stringSize; i++)
    {
        if ((string + i) == pointerToRemove) {
            for (j = i; j < stringSize - 1; j++)
            {
                string[j] = string[j + 1];
            }
            string[j] = '\0';
        }
    }
}

void mergeSort(char** arr, int size, int flagPosition)
{
    // the function implement merge sort, with option to smaller number
    // to bigger number and from bigger number to smaller using the flag position
    char** tmpArr = NULL;
    if (size <= 1)
        return;

    mergeSort(arr, size / 2, flagPosition);
    mergeSort(arr + size / 2, size - size / 2, flagPosition);

    tmpArr = (char**)malloc(size * sizeof(char*));
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

void merge(char** arr1, int sizeArr1, char** arr2, int sizeArr2, char** resArr, int flagPosition)
{
    // the function merge 2 arrays, if the flag position is positive the merge will be from the smaller number to bigger
    int indexArr1, indexArr2, indexArrRes;
    indexArr1 = indexArr2 = indexArrRes = 0;

    while ((indexArr1 < sizeArr1) && (indexArr2 < sizeArr2)) {
        if (flagPosition ? *(arr1 + indexArr1) <= *(arr2 + indexArr2) : *(arr1 + indexArr1) >= *(arr2 + indexArr2)) {
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


void copyArr(char** dest, char** src, int size)
{
    // the function get array from dest and copy it to the src
    int i;

    for (i = 0; i < size; i++)
        dest[i] = src[i];
}

int getSizeOfPointerArray(char** arr) {
    int index = 0;
    int count = 0;
    while (*(arr + index) != NULL)
    {
        index++;
    }
    return index;
}

char** getStrArrayInput(unsigned int* arrSize) {
    int maxCharSize = 1;
    char* stringToSet;
    char singleChar;
    int stringToSetIndex = 0;
    char** stringArr;
    scanf("%d", arrSize);
    stringArr = (char**)malloc(sizeof(char*) * (*arrSize));
    if (!stringArr) {
        exit(1);
    }
    singleChar = getchar();

    for (int i = 0; i < *arrSize; i++) {
        stringToSet = (char*)malloc(sizeof(char) * (maxCharSize + 1));
        if (!stringToSet) {
            exit(1);
        }
        stringToSet[0] = '\0';
        singleChar = getchar();
        while (singleChar != '\n') {
            stringToSet[stringToSetIndex] = singleChar;
            stringToSet[stringToSetIndex + 1] = '\0';
            stringToSetIndex++;
            if (stringToSetIndex == maxCharSize) {
                maxCharSize *= 2;
                stringToSet = (char*)realloc(stringToSet, sizeof(char) * (maxCharSize + 1));
                if (!stringToSet) {
                    exit(1);
                }
            }
            singleChar = getchar();
        }
        *(stringArr + i) = stringToSet;
        stringToSetIndex = 0;
        maxCharSize = 1;
    }
    return stringArr;
}
