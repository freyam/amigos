#ifndef AMIGOS_H
#define AMIGOS_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef char string[50];

typedef struct User User;
struct User {
    int uid;
    string name;
    string age;
    string gender;
    string email;
    string ip;
    string job_title;
    string location;
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

// Core UI and UX Functions
void banner();
void authorization();
void initialize();
void mainMenu();
void userMenu();
void friendMenu();

// Frienship Network Functions
Graph *createGraph(int);
void addFriendship(Graph *, User, User);
void displayFriendships(Graph *);
void displayAdjacencyList(Graph *);

// User Functions
User *createUser(User);
void printUser(User);
void adduser(Graph *, Heap *);
void autofill(Graph *);
void importData(Graph *);

void searchMenu(Graph *);
void searchUID(Graph *);
void searchName(Graph *);

void editMenu(Graph *);
void editUID(Graph *);
void editName(Graph *);

void displayUsers(Graph *);

void removeMenu(Graph *);
void removeUID(Graph *, Heap *h);
void removeName(Graph *, Heap *h);

// Project Functions
void recommendFriends(Graph *); // TODO
void checkFriendship(Graph *);

// Queue Functions (for BFS)
Queue *createQueue();
void enqueue(Queue *, User);
User dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);
void bfs(Graph *, User);

// Min Heap Functions (for Minimum Index)
Heap *createHeap(int);
void insertHeap(Heap *, int);
void printHeap(Heap *);
void heapify_bottom_top(Heap *, int);
void heapify_top_bottom(Heap *, int);
int PopMin(Heap *h);

void quit();

#endif
