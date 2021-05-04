#include "amigos.h"

User null_user = {0, "", "", "", "", "", "", ""};

extern int V;

void bfs(Graph *graph, User startVertex) {
    Queue *q = createQueue();

    graph->visited[startVertex.uid] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        // printQueue(q);
        User currentVertex = dequeue(q);
        printf("Visited %s\n", currentVertex.name);

        User *temp = graph->adjList[currentVertex.uid];

        while (temp) {
            User adjVertex = *temp;

            if (graph->visited[adjVertex.uid] == 0) {
                graph->visited[adjVertex.uid] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue *q) {
    return (q->rear == -1);
}

void enqueue(Queue *q, User value) {
    if (q->rear == V - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

User dequeue(Queue *q) {
    User item;
    if (isEmpty(q)) {
        printf("The Queue is Empty");
        item = null_user;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            printf("Resetting Queue\n");
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
            printf("%s ", q->items[i].name);
        }
        printf("\n");
    }
}