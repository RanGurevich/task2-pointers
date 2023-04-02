//#define _CRT_SECURE_NO_WARNINGS
//#define SIZE 100
#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//
//void pointerSort(int* arr, unsigned int size, int ascend_flag, int*** pointers);
//void printPointers(int** arr, int size);
//void mergeSort(int* arr, int size, int flagPosition);
//void merge(int* arr1, int sizeArr1, int* arr2, int sizeArr2, int* resArr, int flagPosition);
//void copyArr(int dest[], int src[], int size);
//
//void main() {
//	// This program sorting array and return pointer array
//	/*
//	* Name: Ran Gurevich
//	* ID: 207685504
//	* TASK NUMBER 2: 1-B
//	*/
//
//	unsigned int size, i;
//	int arr[SIZE];
//	int** pointers;
//	int ascend_flag;
//
//	printf("Please enter the number of items:\n");
//	scanf("%u", &size);
//
//	for (i = 0; i < size; i++)
//		scanf("%d", &arr[i]);
//
//	scanf("%d", &ascend_flag);
//
//	pointerSort(arr, size, ascend_flag, &pointers);
//	printf("The sorted array:\n"); //Print the sorted array
//	printPointers(pointers, size);
//	free(pointers);
//}
//
//void pointerSort(int* arr, unsigned int size, int ascend_flag, int*** pointers) {
//	// the function sorting the array and return array of the pointers of the given array
//	int i;
//	*pointers = (int**)(malloc(sizeof(int**) * size));
//	mergeSort(arr, size, ascend_flag);
//	for (i = 0; i < size; i++)
//	{
//		**(pointers + i) = (arr + i);
//	}
//}
//
//void mergeSort(int* arr, int size, int flagPosition)
//{
//	// the function implement merge sort, with option to smaller number
//	// to bigger number and from bigger number to smaller using the flag position
//	int* tmpArr = NULL;
//	if (size <= 1)
//		return;
//
//	mergeSort(arr, size / 2, flagPosition);
//	mergeSort(arr + size / 2, size - size / 2, flagPosition);
//
//	tmpArr = (int*)malloc(size * sizeof(int));
//	if (tmpArr)
//	{
//		merge(arr, size / 2, arr + size / 2, size - size / 2, tmpArr, flagPosition);
//		copyArr(arr, tmpArr, size); // copy values from tmpArr to arr
//		free(tmpArr);
//	}
//	else
//	{
//		printf("Memory allocation failure!!!\n");
//		exit(1);	// end program immediately with code 1 (indicating an error)
//	}
//}
//
//void merge(int* arr1, int sizeArr1, int* arr2, int sizeArr2, int* resArr, int flagPosition)
//{
//	// the function merge 2 arrays, if the flag position is positive the merge will be from the smaller number to bigger
//	int indexArr1, indexArr2, indexArrRes;
//	indexArr1 = indexArr2 = indexArrRes = 0;
//
//	while ((indexArr1 < sizeArr1) && (indexArr2 < sizeArr2)) {
//		if (flagPosition ? arr1[indexArr1] <= arr2[indexArr2] : arr1[indexArr1] >= arr2[indexArr2]) {
//			resArr[indexArrRes] = arr1[indexArr1];
//			indexArr1++;
//		}
//		else {
//			resArr[indexArrRes] = arr2[indexArr2];
//			indexArr2++;
//		}
//		indexArrRes++;
//	}
//
//	while (indexArr1 < sizeArr1) {
//		resArr[indexArrRes] = arr1[indexArr1];
//		indexArr1++;
//		indexArrRes++;
//	}
//	while (indexArr2 < sizeArr2) {
//		resArr[indexArrRes] = arr2[indexArr2];
//		indexArr2++;
//		indexArrRes++;
//	}
//}
//
//void printPointers(int** arr, int size)
//{
//	// the function gets array of pointers and prints the value of each one
//	int i;
//	for (i = 0; i < size; i++)
//		printf("%d ", **(arr + i));
//	printf("\n");
//}
//
//void copyArr(int dest[], int src[], int size)
//{
//	// the function get array from dest and copy it to the src
//	int i;
//
//	for (i = 0; i < size; i++)
//		dest[i] = src[i];
//}

void main() {
	printf("!");
}