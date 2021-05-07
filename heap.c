#include "amigos.h"

Heap *createHeap(int capacity) {
	Heap *h = (Heap *)malloc(sizeof(Heap));

	h->count = 0;
	h->capacity = capacity;
	h->arr = (int *)malloc(capacity * sizeof(int));
	return h;
}

void insertHeap(Heap *h, int key) {
	if (h->count < h->capacity) {
		h->arr[h->count] = key;
		heapify_bottom_top(h, h->count);
		h->count++;
	}
}

void heapify_bottom_top(Heap *h, int index) {
	int temp;
	int parent_node = (index - 1) / 2;

	if (h->arr[parent_node] > h->arr[index]) {
		temp = h->arr[parent_node];
		h->arr[parent_node] = h->arr[index];
		h->arr[index] = temp;
		heapify_bottom_top(h, parent_node);
	}
}

void heapify_top_bottom(Heap *h, int parent_node) {
	int left = parent_node * 2 + 1;
	int right = parent_node * 2 + 2;
	int min;
	int temp;

	if (left >= h->count || left < 0)
		left = -1;
	if (right >= h->count || right < 0)
		right = -1;

	if (left != -1 && h->arr[left] < h->arr[parent_node])
		min = left;
	else
		min = parent_node;
	if (right != -1 && h->arr[right] < h->arr[min])
		min = right;

	if (min != parent_node) {
		temp = h->arr[min];
		h->arr[min] = h->arr[parent_node];
		h->arr[parent_node] = temp;

		heapify_top_bottom(h, min);
	}
}

int PopMin(Heap *h) {
	int pop;
	if (h->count == 0) {
		printf("\nHeap is Empty\n");
		return -1;
	}
	pop = h->arr[0];
	h->arr[0] = h->arr[h->count - 1];
	h->count--;
	heapify_top_bottom(h, 0);
	return pop;
}

void printHeap(Heap *h) {
	int i;
	printf("____________Print Heap_____________\n");
	for (i = 0; i < h->count; i++) {
		printf("-> %d ", h->arr[i]);
	}
	printf("->__/\\__\n");
}