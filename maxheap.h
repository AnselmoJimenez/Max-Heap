#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// indexes of the heap elements
#define PARENT( i )         ( (i - 1) / 2 )
#define LEFT_CHILD( i )     ( 2 * i + 1 )
#define RIGHT_CHILD( i )    ( 2 * (i + 1) )

// maximum size of the heap
#define MAX_SIZE 15

// heap structure
typedef struct {
    int root[MAX_SIZE];
    int count;
} maxheap_t;

// Creates heap and returns a new heap
maxheap_t *create_heap();

// Swaps entries in the heap
void swap(int *a, int *b);

// Swaps the current element up in the heap if needed
void heapifyUp(maxheap_t *heap, int position);

// Swaps the current element down in heap if needed
void heapifyDown(maxheap_t *heap, int position);

// Inserts a new element in the heap with given data
void insert(maxheap_t *heap, int data);

// Removes an element in the heap
void delete(maxheap_t *heap, int position);

// return maximum element
int getMax(maxheap_t *heap);

// generates a heap from an existing array
maxheap_t *buildHeap(int *array, int arraySize);

// sorts heap. returns sorted array
void heapSort(int *array, int arraySize);

// Print heap
void printHeap(maxheap_t *heap);