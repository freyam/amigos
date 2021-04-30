#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friendsbook.h"

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

void addEdge(Graph *graph, User src, User dest) {
    User *newUser = createUser(dest);
    newUser->next = graph->adjList[src.uid];
    graph->adjList[src.uid] = newUser;

    // newUser = createUser(src);
    // newUser->next = graph->adjList[dest.uid];
    // graph->adjList[dest.uid] = newUser;
}

User *createUser(User v) {
    User *newUser = malloc(sizeof(User));
    newUser->uid = v.uid;
    strcpy(newUser->name, v.name);
    newUser->age = v.age;
    strcpy(newUser->city, v.city);
    newUser->next = NULL;
    return newUser;
}

void adduser(Graph *g) {
    User u;
    printf("Enter the details\n");
    u.uid = 1;
    printf("Name: ");
    scanf("%s", u.name);
    printf("Age: ");
    scanf("%d", &u.age);
    printf("City: ");
    scanf("%s", u.city);

    User *newUser = createUser(u);

    printUser(u);
}

void searchuser(Graph *g) {
}

void edituser(Graph *g) {
}

void displayuser(Graph *g) {
}

void removeuser(Graph *g) {
}

void recommendfriend() {
}

void displayfriendgraph() {
}

void checkfriend() {
}