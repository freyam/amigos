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

void bfs(Graph *g, User startVertex) {
    Queue *q = createQueue();

    g->visited[startVertex.uid] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        printQueue(q);
        User currentVertex = dequeue(q);
        printf("Visited %s\n", currentVertex.name);

        User *temp = g->adjList[currentVertex.uid];

        while (temp) {
            User adjVertex = *temp;

            if (g->visited[adjVertex.uid] == 0) {
                g->visited[adjVertex.uid] = 1;
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
    Graph *g = malloc(sizeof(Graph));
    g->V = vertices;

    g->adjList = malloc(vertices * sizeof(User *));
    g->visited = malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        g->adjList[i] = NULL;
        g->visited[i] = 0;
    }

    return g;
}

void addFriendship(Graph *g, User src, User dest) {
    User *newUser = createUser(dest);
    newUser->next = g->adjList[src.uid];
    g->adjList[src.uid] = newUser;

    // newUser = createUser(src);
    // newUser->next = g->adjList[dest.uid];
    // g->adjList[dest.uid] = newUser;
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
    Graph *g = createGraph(6);
    User u[6] = {{-1, "", -1, ""},
                 {1, "Freyam", 19, "Ahmedabad"},
                 {2, "Lokesh", 19, "Chennai"},
                 {3, "Freya", 22, "Abu Dhabi"},
                 {4, "Tejal", 48, "Abu Dhabi"},
                 {5, "Bhushan", 51, "Kanpur"}};

    addFriendship(g, u[1], u[2]);
    addFriendship(g, u[1], u[3]);
    addFriendship(g, u[2], u[3]);
    addFriendship(g, u[2], u[5]);
    addFriendship(g, u[2], u[4]);
    addFriendship(g, u[3], u[5]);
    addFriendship(g, u[4], u[5]);

    bfs(g, u[1]);

    return 0;
}