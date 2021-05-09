#ifndef AMIGOS_H
#define AMIGOS_H

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
  int friend_id;
  treeNode *left_child;
  treeNode *right_child;
  int height;
};

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

  treeNode *friend_list;
};

typedef struct FriendNetwork FriendNetwork;
struct FriendNetwork {
  int V;          // number of users
  int minUID;     // number of registered users
  User *userList; // the user list
};

typedef struct Queue Queue;
struct Queue {
  int *items;
  int front;
  int rear;
};

typedef struct Heap Heap;
struct Heap {
  int *arr;
  int count;
  int capacity;
};

typedef struct intx intx;
struct intx {
  int val;
  int idx;
};

// Core UI and UX Functions
void banner();
void authentication();
void initialize();
void mainMenu();
void userMenu();
void friendMenu();

// Frienship Network Functions
FriendNetwork *createGraph(int);

// User Manangement Functions
User *createUser(User);
int findUID();
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
void addFriendship(int, int);

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
void displayFriendshipNetwork();
void writeFriendshipNetwork();
void ViewFriendshipNetwork();

// AVL Functions (for the Friendlist)
int height(treeNode *);
int max(int, int);
treeNode *newNode(int);
treeNode *rightRotate(treeNode *);
treeNode *leftRotate(treeNode *);
int getBalance(treeNode *);
treeNode *insertTreeNode(treeNode *, int);
treeNode *minValueNode(treeNode *);
treeNode *deleteNode(treeNode *, int);
void printPreOrder(treeNode *);
bool findFriend(treeNode *, int);
void printFriendlist(treeNode *);
void writeFriendlist(treeNode *, FILE *);
void singlePass(treeNode *, Queue *, bool[]);

// Queue Functions (for BFS)
Queue *createQueue(int size);
void enqueue(Queue *, int);
int dequeue(Queue *);
void display(Queue *);
bool isEmpty(Queue *);
void printQueue(Queue *);
void bfs(treeNode *, bool[]);

// Min Heap Functions (for Minimum UID)
Heap *createHeap(int);
void insertHeap(Heap *, int);
void printHeap(Heap *);
void heapify_bottom_top(Heap *, int);
void heapify_top_bottom(Heap *, int);
int PopMin(Heap *token);

void quit();

#endif
