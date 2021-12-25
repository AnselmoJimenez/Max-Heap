#include "maxheap.h"

// Creates heap and returns a new heap
maxheap_t *createHeap() {
    //  allocate memory for the heap
    maxheap_t *heap = (maxheap_t *) malloc(sizeof(maxheap_t));

    // initialize all entries to 0 and count to 0
    for (int i = 0; i < MAX_SIZE; i++) { 
        heap->root[i] = *(int *) " "; 
    }
    heap->count = 0;

    return heap;
}

// Frees th allocated min heap
void destroyHeap(maxheap_t *heap) {
    if (heap == NULL) { return; }

    free(heap);
    heap = NULL;
}

// Swaps entries in the heap
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Swaps the current element up in the heap if needed
void heapifyUp(maxheap_t *heap, int position) {
    // Error clauses. Check for emptiness.
    if (heap->count == 0) { return; }

    // defining parent index in heap
    int parent = PARENT(position);

    // Checking if the position < parent and if parent exists
    if (parent > -1 && heap->root[parent] < heap->root[position]) {
        swap(&heap->root[position], &heap->root[parent]);
        heapifyUp(heap, parent);
    }
}

// Swaps the current element down in heap if needed
void heapifyDown(maxheap_t *heap, int position) {
    int leftChild = LEFT_CHILD(position);
    int rightChild = RIGHT_CHILD(position);
    int child = position;

    // Check if left child exists and if left child < position
    if (leftChild < heap->count && heap->root[leftChild] > heap->root[child]) { child = leftChild; }
    
    // Check if the right child exists and if right child < position
    if (rightChild < heap->count && heap->root[rightChild] > heap->root[child]) { child = rightChild; }
    
    // Check the min heap condition
    if (position != child) {
        swap(&heap->root[child], &heap->root[position]);
        heapifyDown(heap, child);
    }
}

// Inserts a new element in the heap with given data
void insert(maxheap_t *heap, int data) {
    // ERROR CLAUSES. max capacity.
    if (heap->count == MAX_SIZE) { 
        printf("the Heap is at max capacity.\n"); 
        return;
    }

    // insert new data at the end of the heap and place in correct spot
    heap->root[heap->count] = data;
    heapifyUp(heap, heap->count);

    // Increase size of the heap by 1
    heap->count += 1;
}

// Removes an element in the heap
void delete(maxheap_t *heap, int position) {
    // Checking bounds
    if (0 > position || position > heap->count - 1) { printf("Invalid position.\n"); return; }

    // defining indexes
    int parent = PARENT(position);
    int leftChild = LEFT_CHILD(position);
    int rightChild = RIGHT_CHILD(position);

    // bring the last position to fill in the removed position; reset the last position; decrement total num of nodes
    heap->root[position] = heap->root[heap->count - 1];
    heap->root[heap->count - 1] = *(int *) " ";
    heap->count--;

    if (parent > -1 && heap->root[parent] < heap->root[position]) {
        heapifyUp(heap, position);
    }
    if (leftChild < heap->count && heap->root[position] < heap->root[leftChild] || rightChild < heap->count && heap->root[position] < heap->root[rightChild]) {
        heapifyDown(heap, position);
    }
}

// return maximum element
int getMax(maxheap_t *heap) {
    if (heap == NULL) { printf("Empty Heap.\n"); return 0; }
    return heap->root[0];
}

// generates a heap from an existing array
maxheap_t *buildHeap(int *array, int arraySize) {
    maxheap_t *new_heap = create_heap();
    memcpy(new_heap->root, array, arraySize * sizeof(int));
    new_heap->count = arraySize;

    for (int i = (arraySize / 2) - 1; i >= 0; i--) {
        heapifyDown(new_heap, i);
    }

    return new_heap;
}

// sorts heap. returns sorted array
void heapSort(int *array, int arraySize) {
    maxheap_t *new_heap = buildHeap(array, arraySize);

    for (int i = arraySize - 1; i > -1; i--) {
        swap(&new_heap->root[0], &new_heap->root[i]);
        new_heap->count--;
        
        heapifyDown(new_heap, 0);
    }

    memcpy(array, new_heap->root,  arraySize * sizeof(int));
}

// Print heap
void printHeap(maxheap_t *heap) {
    if (heap == NULL) { printf("Empty Heap.\n"); return; }
    
    for (int i = 0; i < MAX_SIZE; i++) {
        if (heap->root[i] == *(int *) " ") { printf("\n"); return; };
        printf("%d ", heap->root[i]);
    }
    printf("\n");
}