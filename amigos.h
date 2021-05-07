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


int BLACK=0;
int RED=1;


typedef struct User User;
struct User {
	int uid;
	string
		name,
		age,
		gender,
		email,
		ip,
		job_title,
		location;
	User *next;
};

struct node {
	struct User *data; // data
	int color; // 1-RED, 0-BLACK
	struct node *parent; // parent
	struct node *right; // right-child
	struct node *left; // left child
};

struct vertex {
	struct User *User;
    struct node *root;
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


void swapColors(struct node *x1, struct node *x2);
void swapValues(struct node *u, struct node *v);
bool hasRedChild(struct node *x);


struct node *RedBlackTree(struct node *head,struct node *temp);
struct node *rightrotate(struct node *head ,struct node *temp);
struct node *leftrotate(struct node *head ,struct node *temp);
struct node *restructure(struct node *head, struct node *pt);


struct node *siblingfind(struct node *x) ;
struct node *unclefind(struct node *x);
struct node *fixRedRed(struct node *head,struct node *x);
struct node *successor(struct node *x);
struct node *BSTreplace(struct node *x);
struct node *fixDoubleBlack(struct node *head,struct node *x);
struct node *deleteNode(struct node *head ,struct node *v);
struct node *search(struct node *head,int n);
struct node *deleteByVal(struct node *head,int n);

#endif
