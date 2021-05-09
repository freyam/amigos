#include "amigos.h"

void countingSort(intx scores[], int size) {
  intx temp[size];
  for (int i = 0; i < size; ++i) {
    temp[i].idx = i;
    temp[i].val = 0;
  }
  int max = scores[0].val;
  for (int i = 1; i < size; i++)
    if (scores[i].val > max)
      max = scores[i].val;

  int count[101];

  for (int i = 0; i <= max; ++i)
    count[i] = 0;

  for (int i = 0; i < size; i++)
    count[scores[i].val]++;

  for (int i = 1; i <= max; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    temp[count[scores[i].val] - 1] = scores[i];
    count[scores[i].val]--;
  }

  for (int i = 0; i < size; i++)
    scores[i] = temp[i];

  for (int low = 0, high = size - 1; low < high; low++, high--) {
    intx temp = scores[low];
    scores[low] = scores[high];
    scores[high] = temp;
  }
}

void printINTXArray(intx arr[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("[%d] %d ", arr[i].idx, arr[i].val);
  }
  printf("\n");
}

int main() {
  intx array[11] = {{0, 0}, {40, 1}, {78, 2}, {34, 3}, {9, 4}, {0, 5}, {1, 6}, {76, 7}, {79, 8}, {80, 9}, {30, 10}};

  printINTXArray(array, 11);
  countingSort(array, 11);
  printINTXArray(array, 11);
}