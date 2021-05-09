#include "amigos.h"

Heap *createHeap(int capacity) {
  Heap *token = (Heap *)malloc(sizeof(Heap));

  token->count = 0;
  token->capacity = capacity;
  token->arr = (int *)malloc(capacity * sizeof(int));
  return token;
}

void insertHeap(Heap *token, int key) {
  if (token->count < token->capacity) {
    token->arr[token->count] = key;
    heapify_bottom_top(token, token->count);
    token->count++;
  }
}

void heapify_bottom_top(Heap *token, int index) {
  int temp;
  int parent_node = (index - 1) / 2;

  if (token->arr[parent_node] > token->arr[index]) {
    temp = token->arr[parent_node];
    token->arr[parent_node] = token->arr[index];
    token->arr[index] = temp;
    heapify_bottom_top(token, parent_node);
  }
}

void heapify_top_bottom(Heap *token, int parent_node) {
  int left = parent_node * 2 + 1;
  int right = parent_node * 2 + 2;
  int min;
  int temp;

  if (left >= token->count || left < 0)
    left = -1;
  if (right >= token->count || right < 0)
    right = -1;

  if (left != -1 && token->arr[left] < token->arr[parent_node])
    min = left;
  else
    min = parent_node;
  if (right != -1 && token->arr[right] < token->arr[min])
    min = right;

  if (min != parent_node) {
    temp = token->arr[min];
    token->arr[min] = token->arr[parent_node];
    token->arr[parent_node] = temp;

    heapify_top_bottom(token, min);
  }
}

int PopMin(Heap *token) {
  int pop;
  if (token->count == 0) {
    printf("\nHeap is Empty\n");
    return -1;
  }
  pop = token->arr[0];
  token->arr[0] = token->arr[token->count - 1];
  token->count--;
  heapify_top_bottom(token, 0);
  return pop;
}

// void printHeap(Heap *token) {
//   int i;
//   printf("____________Print Heap_____________\n");
//   for (i = 0; i < token->count; i++) {
//     printf("-> %d ", token->arr[i]);
//   }
//   printf("->__/\\__\n");
// }