#include "amigos.h"

unsigned long int minidx = 1;

unsigned long int findidx(Heap *h) {
    // printf("%ld %d\n", minidx, h->arr[0]);
    if (h->count == 0 || minidx <= h->arr[0])
        return minidx++;
    else
        return PopMin(h);
}

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
void adduser(Graph *g, Heap *h) {
    User u;
    u.uid = findidx(h);
    printf("Enter the details of User [%03ld]\n", u.uid);
    printf("Name: ");
    scanf("%s", u.name);
    printf("Age: ");
    scanf("%d", &u.age);
    printf("City: ");
    scanf("%s", u.city);

    g->adjList[u.uid] = createUser(u);
    printuser(*(g->adjList[u.uid]));
}

void autofill(Graph *g) {
    User u[9] = {{0, "", 0, ""},
                 {1, "Freyam", 19, "Ahmedabad"},
                 {2, "Lokesh", 19, "Chennai"},
                 {3, "Freya", 22, "Abu Dhabi"},
                 {4, "Tejal", 48, "Abu Dhabi"},
                 {5, "Bhushan", 51, "Kanpur"},
                 {6, "Varshita", 19, "Ruwais"},
                 {7, "Swetha", 19, "Sharjah"},
                 {8, "Shubh", 19, "Doha"}};

    if (minidx == 1)
        for (int i = 1; i <= 8; ++i)
            g->adjList[minidx++] = createUser(u[i]);
    else
        for (int i = 1; i <= 8; ++i)
            g->adjList[i] = createUser(u[i]);

    displayusers(g);
    system("sleep 1");
    clrscr;
}

void printuser(User u) {
    printf("[%03ld] - %10s - %02d - %10s\n", u.uid, u.name, u.age, u.city);
}

void searchuserbyuid(Graph *g) {
    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);
    if (g->adjList[uid])
        printuser(*(g->adjList[uid]));
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
            printuser(*(g->adjList[i]));
            found = 1;
            break;
        }
    if (!found)
        printf("No User with Name \"%s\".", name);
    printf("\n");
}

void edituserbyuid(Graph *g) {
    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);
    if (g->adjList[uid]) {
        printuser(*(g->adjList[uid]));
        printf("\n");
        printf("Enter the new details\n");
        printf("Name: ");
        scanf("%s", g->adjList[uid]->name);
        printf("Age: ");
        scanf("%d", &g->adjList[uid]->age);
        printf("City: ");
        scanf("%s", g->adjList[uid]->city);

        printf("Edited.\n");
        printuser(*(g->adjList[uid]));
    } else
        printf("No User with UID #%d.", uid);
    printf("\n");
}

void edituserbyname(Graph *g) {
    bool found = 0;
    string name;
    printf("Enter the Name: ");
    scanf("%s", name);
    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
            printuser(*(g->adjList[i]));
            printf("\n");
            printf("Enter the new details\n");
            printf("Name: ");
            scanf("%s", g->adjList[i]->name);
            printf("Age: ");
            scanf("%d", &g->adjList[i]->age);
            printf("City: ");
            scanf("%s", g->adjList[i]->city);

            printf("Edited.\n");
            printuser(*(g->adjList[i]));
            found = 1;
            break;
        }
    if (!found)
        printf("No User with Name \"%s\".", name);
    printf("\n");
}

void displayusers(Graph *g) {
    system("clear");

    bool found = 0;

    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i]) {
            if (!found)
                found = 1;
            printuser(*(g->adjList[i]));
        }

    if (!found)
        printf("User Database is Empty!");

    printf("\n");
}

void removeuserbyuid(Graph *g, Heap *h) {
    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);
    if (g->adjList[uid]) {
        printuser(*(g->adjList[uid]));
        printf("Confirm Delete (y/n)? ");
        char c, buff;
        scanf("%c%c", &c, &buff);
        if (c != 'n') {
            insertHeap(h, uid);
            g->adjList[uid]->age = 0;
            g->adjList[uid]->uid = INT_MAX;
            strcpy(g->adjList[uid]->name, "");
            strcpy(g->adjList[uid]->city, "");
            g->adjList[uid] = NULL;
        }
    } else
        printf("No User with UID #%d.", uid);
    printf("\n");
}

void removeuserbyname(Graph *g, Heap *h) {
    bool found = 0;
    string name;
    printf("Enter the Name: ");
    scanf("%s", name);
    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
            printuser(*(g->adjList[i]));
            printf("Confirm Delete (y/n)? ");
            char c, buff;
            scanf("%c%c", &c, &buff);
            if (c != 'n') {
                insertHeap(h, i);
                g->adjList[i]->age = 0;
                g->adjList[i]->uid = INT_MAX;
                strcpy(g->adjList[i]->name, "");
                strcpy(g->adjList[i]->city, "");
                g->adjList[i] = NULL;
                found = 1;
                break;
            }
        }
    if (!found)
        printf("No User with Name \"%s\".", name);
    printf("\n");
}

void recommendfriend(Graph *g) {
}

void displayFriendshipGraph(Graph *g) {
}

void checkfriend(Graph *g) {
}