#ifndef AMIGOS
#define AMIGOS

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clrscr system("clear")

typedef char string[50];

typedef struct User User;
struct User {
    unsigned long int uid;
    string name;
    int age;
    string city;
    string gender;
    string institution;
    User *next;
};

typedef struct Graph Graph;
struct Graph {
    int V;          // number of vertices
    User **adjList; // the adjacency list
    bool *visited;  // a boolean array
};

typedef struct Queue Queue;
struct Queue {
    User items[100];
    int front;
    int rear;
};

typedef struct Heap Heap;
struct Heap {
    int *arr;
    int count;
    int capacity;
};

// Interface Functions
void banner();
void mainmenu();
void usermenu();
void friendmenu();

// Frienship Network Functions
Graph *createGraph(int);
void addEdge(Graph *, User, User);
void displayFriendshipGraph(Graph *); // TODO

// User Functions
User *createUser(User);
void printuser(User);
void adduser(Graph *, Heap *);
void autofill(Graph *);
void searchusermenu(Graph *);
void searchuserbyuid(Graph *);
void searchuserbyname(Graph *);
void editusermenu(Graph *);
void edituserbyuid(Graph *);
void edituserbyname(Graph *);
void displayusers(Graph *);
void removeusermenu(Graph *);
void removeuserbyuid(Graph *, Heap *h);
void removeuserbyname(Graph *, Heap *h);

// Project Functions
void recommendfriend(Graph *); // TODO
void checkfriend(Graph *);     // TODO

// Queue Functions (for BFS)
Queue *createQueue();
void enqueue(Queue *, User);
User dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);

// Min Heap Functions (for Minimum Index)
Heap *createHeap(int);
void insertHeap(Heap *, int);
void printHeap(Heap *);
void heapify_bottom_top(Heap *, int);
void heapify_top_bottom(Heap *, int);
int PopMin(Heap *h);

void quit();

#endif
