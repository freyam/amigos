#ifndef AMIGOS_H
#define AMIGOS_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef char string[50];

#define gets(s) \
  getchar();    \
  scanf("%[^\n]s", s);

typedef struct treeNode treeNode;
struct treeNode {
  int friendid;
  treeNode *leftchild;
  treeNode *rightchild;
  int height;
};

typedef struct User User;
struct User {
  int uid;
  string name,
      age,
      gender,
      email,
      job_title,
      university,
      city,
      country;

  treeNode *friendlist;
};

typedef struct Graph Graph;
struct Graph {
  int V;          // number of users
  int minUID;     // number of registered users
  User *userList; // the user list
  bool *visited;
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

typedef struct intidx intidx;
struct intidx {
  int val;
  int idx;
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
void addUser();
void importData();

void searchUserMenu();
void searchUserUID();
void searchUserName();

void editUserMenu();
void editUserUID();
void editUserName();

void displayUserDatabase();

void removeUserMenu();
void removeUserUID();
void removeUserName();

// Friend Manangement Functions
void addFriendship(User, User);

void addFriendMenu();
void addFriendshipUID();
void addFriendshipName();

void recommendFriendsMenu();
int compatibilityScore(User, User);
void recommendFriendsNewUser();
void recommendFriendsExistingUser();

void checkFriendMenu();
void checkFriendshipUID();
void checkFriendshipName();

void displayFriendsMenu();
void displayFriendsAdjacencyList();
void writeFriendshipNetwork();
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
