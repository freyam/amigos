#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

typedef char string[25];

typedef struct User User;
struct User {
    int uid;
    string name;
    int age;
    string location;
    User *next;
};
User null_user = {0, "", 0, ""};

User *createUser(User);

typedef struct Queue Queue;
struct Queue {
    User items[SIZE];
    int front;
    int rear;
};

typedef struct Graph Graph;
struct Graph {
    int V;          // number of vertices
    User **adjList; // the adjacency list
    bool *visited;  // a boolean array
};

Queue *createQueue();
void enqueue(Queue *, User);
User dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);

void bfs(Graph *graph, User startVertex) {
    Queue *q = createQueue();

    graph->visited[startVertex.uid] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        printQueue(q);
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

User *createUser(User v) {
    User *newUser = malloc(sizeof(User));
    newUser->uid = v.uid;
    strcpy(newUser->name, v.name);
    newUser->age = v.age;
    strcpy(newUser->location, v.location);
    newUser->next = NULL;
    return newUser;
}

Graph *createGraph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->V = vertices;

    graph->adjList = malloc(vertices * sizeof(User *));
    graph->visited = malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addFriendship(Graph *graph, User src, User dest) {
    User *newUser = createUser(dest);
    newUser->next = graph->adjList[src.uid];
    graph->adjList[src.uid] = newUser;

    // newUser = createUser(src);
    // newUser->next = graph->adjList[dest.uid];
    // graph->adjList[dest.uid] = newUser;
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
    if (q->rear == SIZE - 1)
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

void printUser(User u) {
    printf("[%05ld] - %10s - %d - %10s\n", u.uid, u.name, u.age, u.location);
}

int main() {
    Graph *graph = createGraph(6);
    User u[6] = {{-1, "", -1, ""},
                 {1, "Freyam", 19, "Ahmedabad"},
                 {2, "Lokesh", 19, "Chennai"},
                 {3, "Freya", 22, "Abu Dhabi"},
                 {4, "Tejal", 48, "Abu Dhabi"},
                 {5, "Bhushan", 51, "Kanpur"}};

    addFriendship(graph, u[1], u[2]);
    addFriendship(graph, u[1], u[3]);
    addFriendship(graph, u[2], u[3]);
    addFriendship(graph, u[2], u[5]);
    addFriendship(graph, u[2], u[4]);
    addFriendship(graph, u[3], u[5]);
    addFriendship(graph, u[4], u[5]);

    bfs(graph, u[1]);

    return 0;
}