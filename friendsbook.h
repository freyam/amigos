#ifndef FRIENDSBOOK
#define FRIENDSBOOK

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
    User *next;
};

typedef struct Queue Queue;
struct Queue {
    User items[100];
    int front;
    int rear;
};

typedef struct Graph Graph;
struct Graph {
    int V;          // number of vertices
    User **adjList; // the adjacency list
    bool *visited;  // a boolean array
};

// Queue Functions (for BFS)
Queue *createQueue();
void enqueue(Queue *, User);
User dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);

// Interface Functions
void banner();
void mainmenu();
void usermenu();
void friendmenu();

// Frienship Network Functions
Graph *createGraph(int);
void addEdge(Graph *, User, User);
void displayfriendgraph(Graph *); // TODO

// User Functions
User *createUser(User);
void printUser(User);
void adduser(Graph *);
void searchusermenu(Graph *);
void searchuserbyuid(Graph *);
void searchuserbyname(Graph *);
void edituser(Graph *); // TODO
void displayuser(Graph *);
void removeuser(Graph *); // TODO

// Project Functions
void recommendfriend(Graph *); // TODO
void checkfriend(Graph *);     // TODO

void quit();

#endif
