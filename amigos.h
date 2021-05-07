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

#define gets(s) \
	getchar();  \
	scanf("%[^\n]s", s);

typedef struct User User;
struct User {
	int uid;
	string
		name,
		age,
		gender,
		email,
		job_title,
		university,
		city,
		country;
	User *next;
};

typedef struct Graph Graph;
struct Graph {
	int V;			 // number of vertices
	User **adjList;	 // the adjacency list
	bool *visited;	 // a boolean array
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

// User Manangement Functions
User *createUser(User);
void printUser(User);
void addUser(Graph *, Heap *);
void importData(Graph *);

void searchUserMenu(Graph *);
void searchUserUID(Graph *);
void searchUserName(Graph *);

void editUserMenu(Graph *);
void editUserUID(Graph *);
void editUserName(Graph *);

void displayUserDatabase(Graph *);

void removeUserMenu(Graph *);
void removeUserUID(Graph *, Heap *h);
void removeUserName(Graph *, Heap *h);

// Friend Manangement Functions
void addFriendship(Graph *, User, User);

void addFriendMenu();
void addFriendshipUID(Graph *);
void addFriendshipName(Graph *);

void recommendFriendsMenu();
int compatibilityScore(User, User);
void recommendFriendsNewUser(Graph *);
void recommendFriendsExistingUser(Graph *);

void checkFriendMenu();
void checkFriendshipUID(Graph *);
void checkFriendshipName(Graph *);

void displayFriendsMenu();
void displayFriendsAdjacencyList(Graph *);
void writeFriendshipNetwork(Graph *);
void ViewFriendshipNetwork();

// Queue Functions (for BFS)
Queue *createQueue();
void enqueue(Queue *, User);
User dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);
void bfs(Graph *, User);

// Min Heap Functions (for Minimum UID)
Heap *createHeap(int);
void insertHeap(Heap *, int);
void printHeap(Heap *);
void heapify_bottom_top(Heap *, int);
void heapify_top_bottom(Heap *, int);
int PopMin(Heap *h);

void quit();

#endif
