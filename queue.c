#include "amigos.h"

// Externing the Global Friend Network
extern FriendNetwork *network;

// Creates a Queue
Queue *createQueue(int size) {
  Queue *q = malloc(sizeof(Queue));
  q->items = malloc(size * sizeof(int));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Checks if a Queue is Empty
bool isEmpty(Queue *q) {
  return (q->rear == -1);
}

// Enqueues (Adds) a new value to the Queue
void enqueue(Queue *q, int value) {
  if (q->rear == network->V - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Dequeues (Removes) a value from the Queue
int dequeue(Queue *q) {
  int item;
  if (isEmpty(q)) {
    printf("The Queue is Empty");
    item = 0;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Prints the values of the Queue
void printQueue(Queue *q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("No Friend Recommendations!");
  } else {
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%s ", network->userList[q->items[i]].name);
    }
    printf("\n");
  }
}