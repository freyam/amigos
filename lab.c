#include "amigos.h"

void countingSort(intidx scores[], int size) {
	intidx temp[size];
	for (int i = 0; i < size; ++i) {
		temp[i].idx = i;
		temp[i].val = 0;
	}
	int max = scores[0].val;
	for (int i = 1; i < size; i++)
		if (scores[i].val > max)
			max = scores[i].val;

	int count[81];

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
}

void reverseArray(intidx arr[], int n) {
	for (int low = 0, high = n - 1; low < high; low++, high--) {
		intidx temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
}

void printINTIDXarray(intidx arr[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("[%d] %d ", arr[i].idx, arr[i].val);
	}
	printf("\n");
}

int main() {
	intidx array[10] = {{30, 0}, {40, 1}, {78, 2}, {34, 3}, {9, 4}, {0, 5}, {1, 6}, {76, 7}, {79, 8}, {80, 9}};

	countingSort(array, 10);
	reverseArray(array, 10);

	printINTIDXarray(array, 10);
}