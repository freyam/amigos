#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[25];
typedef struct User User;

struct User {
    unsigned long int uid;
    string name;
    int age;
    string city;
};

// #define SIZE 40

// struct queue {
//     int items[SIZE];
//     int front;
//     int rear;
// };

// struct queue *createQueue();
// void enqueue(struct queue *q, int);
// int dequeue(struct queue *q);
// void display(struct queue *q);
// int isEmpty(struct queue *q);
// void printQueue(struct queue *q);

// struct node {
//     User u;
//     struct node *next;
// };

// struct node *createNode(User);

// struct Graph {
//     int numVertices;
//     struct node **adjLists;
//     int *visited;
// };

// // BFS algorithm
// void bfs(struct Graph *graph, int startVertex) {
//     struct queue *q = createQueue();

//     graph->visited[startVertex] = 1;
//     enqueue(q, startVertex);

//     while (!isEmpty(q)) {
//         printQueue(q);
//         int currentVertex = dequeue(q);
//         printf("Visited %d\n", currentVertex);

//         struct node *temp = graph->adjLists[currentVertex];

//         while (temp) {
//             int adjVertex = temp->vertex;

//             if (graph->visited[adjVertex] == 0) {
//                 graph->visited[adjVertex] = 1;
//                 enqueue(q, adjVertex);
//             }
//             temp = temp->next;
//         }
//     }
// }

// // Creating a node
// struct node *createNode(User u) {
//     struct node *newNode = malloc(sizeof(struct node));
//     newNode->(u.uid) = u.id;
//     strcpy(newNode->u.name, u.name);
//     newNode->u.age = u.age;
//     strcpy(newNode->u.city, u.city);

//     newNode->next = NULL;
//     return newNode;
// }

// // Creating a graph
// struct Graph *createGraph(int vertices) {
//     struct Graph *graph = malloc(sizeof(struct Graph));
//     graph->numVertices = vertices;

//     graph->adjLists = malloc(vertices * sizeof(struct node *));
//     graph->visited = malloc(vertices * sizeof(int));

//     int i;
//     for (i = 0; i < vertices; i++) {
//         graph->adjLists[i] = NULL;
//         graph->visited[i] = 0;
//     }

//     return graph;
// }

// // Add edge
// void addEdge(struct Graph *graph, int src, int dest) {
//     // Add edge from src to dest
//     struct node *newNode = createNode(dest);
//     newNode->next = graph->adjLists[src];
//     graph->adjLists[src] = newNode;

//     // Add edge from dest to src
//     newNode = createNode(src);
//     newNode->next = graph->adjLists[dest];
//     graph->adjLists[dest] = newNode;
// }

// // Create a queue
// struct queue *createQueue() {
//     struct queue *q = malloc(sizeof(struct queue));
//     q->front = -1;
//     q->rear = -1;
//     return q;
// }

// // Check if the queue is empty
// int isEmpty(struct queue *q) {
//     if (q->rear == -1)
//         return 1;
//     else
//         return 0;
// }

// // Adding elements into queue
// void enqueue(struct queue *q, int value) {
//     if (q->rear == SIZE - 1)
//         printf("\nQueue is Full!!");
//     else {
//         if (q->front == -1)
//             q->front = 0;
//         q->rear++;
//         q->items[q->rear] = value;
//     }
// }

// // Removing elements from queue
// int dequeue(struct queue *q) {
//     int item;
//     if (isEmpty(q)) {
//         printf("Queue is empty");
//         item = -1;
//     } else {
//         item = q->items[q->front];
//         q->front++;
//         if (q->front > q->rear) {
//             printf("Resetting queue ");
//             q->front = q->rear = -1;
//         }
//     }
//     return item;
// }

// // Print the queue
// void printQueue(struct queue *q) {
//     int i = q->front;

//     if (isEmpty(q)) {
//         printf("Queue is empty");
//     } else {
//         printf("\nQueue contains \n");
//         for (i = q->front; i < q->rear + 1; i++) {
//             printf("%d ", q->items[i]);
//         }
//     }
// }

void banner();
void mainmenu();

void usermenu();
void adduser();
void searchuser();
void edituser();
void displayuser();
void removeuser();

void friendmenu();
void recommendfriend();
void displayfriendgraph();
void checkfriend();

void quit();

int main() {
    banner();

    int pass;
    scanf("%d", &pass);
    if (pass != 13) {
        system("clear");
        printf("403 ACCESS DENIED!\n");
        exit(0);
    }

    mainmenu();
    quit();
}

void banner() {
    system("clear");

    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("  **                             **  \n");
    printf("  **           Friends           **  \n");
    printf("  **            Book             **  \n");
    printf("  **                             **  \n");
    printf("  **           Team 13           **  \n");
    printf("  **                             **  \n");
    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("\n");
}

void mainmenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **          Main Menu          **  \n");
        printf("  **                             **  \n");
        printf("  **      1. User Management     **  \n");
        printf("  **     2. Friend Management    **  \n");
        printf("  **                             **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            usermenu();
            break;
        case 2:
            friendmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            mainmenu();
        }
    } while (ch <= 2);
}

void usermenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **        1. Register          **  \n");
        printf("  **        2. Search            **  \n");
        printf("  **        3. Edit              **  \n");
        printf("  **        4. Display           **  \n");
        printf("  **        5. Unregister        **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            adduser();
            break;
        case 2:
            searchuser();
            break;
        case 3:
            edituser();
            break;
        case 4:
            displayuser();
            break;
        case 5:
            removeuser();
            break;
        case 9:
            mainmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            usermenu();
        }
    } while (ch <= 9);
}

void adduser() {
}

void searchuser() {
}

void edituser() {
}

void displayuser() {
}

void removeuser() {
}

void friendmenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **      Friend Management      **  \n");
        printf("  **                             **  \n");
        printf("  **       1. Recommend          **  \n");
        printf("  **       2. Check Status       **  \n");
        printf("  **       3. Display Graph      **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            recommendfriend();
            break;
        case 2:
            checkfriend();
            break;
        case 3:
            displayfriendgraph();
            break;
        case 9:
            mainmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            usermenu();
        }
    } while (ch <= 9);
}

void recommendfriend() {
}

void displayfriendgraph() {
}

void checkfriend() {
}

void quit() {
    system("clear");
    printf("Thank You for visiting us at https://friendsbook.co.in\n");
    exit(0);
}