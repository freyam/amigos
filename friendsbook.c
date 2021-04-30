#include "friendsbook.h"

int minidx = 1;

// Creates the Friendship Network
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

// Creates a new User Node
User *createUser(User v) {
    User *newUser = malloc(sizeof(User));
    newUser->uid = v.uid;
    strcpy(newUser->name, v.name);
    newUser->age = v.age;
    strcpy(newUser->city, v.city);
    newUser->next = NULL;
    return newUser;
}

// Adds a new User to the Friendship Network
void adduser(Graph *g) {
    User u;
    printf("Enter the details\n");
    u.uid = minidx;
    printf("Name: ");
    scanf("%s", u.name);
    printf("Age: ");
    scanf("%d", &u.age);
    printf("City: ");
    scanf("%s", u.city);

    g->adjList[u.uid] = createUser(u);
    printUser(*(g->adjList[u.uid]));
    minidx++;
}

void printUser(User u) {
    printf("[%03ld] - %10s - %02d - %10s\n", u.uid, u.name, u.age, u.city);
}

void searchuserbyuid(Graph *g) {
    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);
    if (g->adjList[uid])
        printUser(*(g->adjList[uid]));
    else
        printf("No User with UID #%d.", uid);
    printf("\n");
}

void searchuserbyname(Graph *g) {
    bool found = 0;
    string name;
    printf("Enter the Name: ");
    scanf("%s", name);
    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
            printUser(*(g->adjList[i]));
            found = 1;
            break;
        }
    if (!found)
        printf("No User with Name \"%s\".", name);
    printf("\n");
}

void searchusermenu(Graph *g) {
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
        printf("  **        Search User          **  \n");
        printf("  **     1. Search by UID        **  \n");
        printf("  **     2. Search by Name       **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the User Menu   **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            searchuserbyuid(g);
            break;
        case 2:
            searchuserbyname(g);
            break;
        case 9:
            usermenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            searchusermenu(g);
        }
    } while (ch <= 9);
}

void edituser(Graph *g) {
    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);
    if (g->adjList[uid]) {
        printUser(*(g->adjList[uid]));
        printf("\n");
        printf("Enter the new details\n");
        printf("Name: ");
        scanf("%s", g->adjList[uid]->name);
        printf("Age: ");
        scanf("%d", &g->adjList[uid]->age);
        printf("City: ");
        scanf("%s", g->adjList[uid]->city);

        printf("Edited.\n");
        printUser(*(g->adjList[uid]));
    } else
        printf("No User with UID #%d.", uid);
    printf("\n");
}

void displayuser(Graph *g) {
    system("clear");
    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i])
            printUser(*(g->adjList[i]));
    printf("\n");
}

void removeuser(Graph *g) {
}

void recommendfriend(Graph *g) {
}

void displayfriendgraph(Graph *g) {
}

void checkfriend(Graph *g) {
}