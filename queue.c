#include "amigos.h"

// User NULLUSER = {0, "", "", "", "", "", "", "", ""};

extern Graph *g;
extern int V;

// Runs the BFS
// void bfs(Graph *g, User startVertex) {
//   Queue *q = createQueue();

//   g->visited[startVertex.uid] = 1;
//   enqueue(q, startVertex);

//   while (!isEmpty(q)) {
//     // printQueue(q);
//     User currentVertex = dequeue(q);
//     printf("Visited %s\n", currentVertex.name);

//     User *temp = g->adjList[currentVertex.uid];

//     while (temp) {
//       User adjVertex = *temp;

//       if (g->visited[adjVertex.uid] == 0) {
//         g->visited[adjVertex.uid] = 1;
//         enqueue(q, adjVertex);
//       }
//       temp = temp->next;
//     }
//   }
// }

// Creates a Queue
Queue *createQueue(int size) {
  Queue *q = malloc(sizeof(Queue));
  q->items = malloc(size * sizeof(int));
  q->front = -1;
  q->rear = -1;
  return q;
}

bool isEmpty(Queue *q) {
  return (q->rear == -1);
}

void enqueue(Queue *q, int value) {
  if (q->rear == V - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

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

void printQueue(Queue *q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("The Queue is Empty");
  } else {
    printf("Queue contains ");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%s ", g->userList[q->items[i]].name);
    }
    printf("\n");
  }
}