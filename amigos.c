#include "amigos.h"

unsigned long int minidx = 1;

Graph *g;
Heap *h;

void authorization() {
    string pass;
    scanf("%s", pass);
    if (strcmp(pass, "team13")) {
        clrscr;
        printf("403 ACCESS DENIED!\n");
        exit(0);
    }
}

void initialize() {
    int N = 100;
    g = createGraph(N);
    h = createHeap(N);

    autofill(g);
    system("sleep 0.5");
}

unsigned long int findidx(Heap *h) {
    // printf("%ld %d\n", minidx, h->arr[0]);
    if (h->count == 0 || minidx <= h->arr[0])
        return minidx++;
    else
        return PopMin(h);
}

// Creates the Friendship Network
Graph *createGraph(int V) {
    Graph *g = malloc(sizeof(Graph));
    g->V = V;

    g->adjList = malloc(V * sizeof(User *));
    g->visited = malloc(V * sizeof(bool));

    for (int i = 0; i < V; i++) {
        g->adjList[i] = NULL;
        g->visited[i] = 0;
    }

    return g;
}

// Creates a new User Node
User *createUser(User u) {
    User *newUser = malloc(sizeof(User));

    newUser->uid = u.uid;
    strcpy(newUser->name, u.name);
    newUser->age = u.age;
    strcpy(newUser->gender, u.gender);
    strcpy(newUser->institution, u.institution);
    strcpy(newUser->city, u.city);
    newUser->next = NULL;

    return newUser;
}

void addEdge(Graph *g, User u, User v) {
    User *newUser = createUser(v);
    newUser->next = g->adjList[u.uid]->next;
    g->adjList[u.uid]->next = newUser;
}

// Adds a new User to the Friendship Network
void adduser(Graph *g, Heap *h) {
    User u;
    u.uid = findidx(h);
    printf("Enter the details of User [%03ld]\n", u.uid);
    printf("Name: ");
    getchar();
    scanf("%[^\n]s", u.name);
    printf("Age: ");
    scanf("%d", &u.age);
    printf("Gender: ");
    getchar();
    scanf("%[^\n]s", u.gender);
    printf("Institution: ");
    getchar();
    scanf("%[^\n]s", u.institution);
    printf("City: ");
    getchar();
    scanf("%[^\n]s", u.city);

    g->adjList[u.uid] = createUser(u);
    printuser(*(g->adjList[u.uid]));
}

void autofill(Graph *g) {
    User u[10] = {{0, "", 0, "", "", ""},
                  {1, "Freyam Mehta", 19, "M", "IIITH", "Ahmedabad"},
                  {2, "Lokesh Venktachalam", 19, "M", "IIITH", "Chennai"},
                  {3, "Freya Mehta", 22, "F", "IIITH", "Abu Dhabi"},
                  {4, "Tejal Mehta", 48, "F", "NITB", "Abu Dhabi"},
                  {5, "Bhushan Mehta", 51, "M", "JCIT", "Kanpur"},
                  {6, "Varshita Kolipaka", 18, "F", "IIITH", "Abu Dhabi"},
                  {7, "Swetha Vipparla", 19, "F", "IIITH", "Sharjah"},
                  {8, "Shubh Agarwal", 19, "M", "IIITH", "Doha"},
                  {9, "Anusha Roy", 18, "F", "IIITH", "Abu Dhabi"}};

    if (minidx == 1)
        for (int i = 1; i <= 9; ++i)
            g->adjList[minidx++] = createUser(u[i]);
    else
        for (int i = 1; i <= 9; ++i)
            g->adjList[i] = createUser(u[i]);

    addEdge(g, u[1], u[2]);
    addEdge(g, u[1], u[3]);
    addEdge(g, u[1], u[4]);
    addEdge(g, u[1], u[5]);
    addEdge(g, u[1], u[6]);
    addEdge(g, u[1], u[7]);
    addEdge(g, u[1], u[8]);
    addEdge(g, u[1], u[9]);
    addEdge(g, u[2], u[1]);
    addEdge(g, u[3], u[4]);
    addEdge(g, u[3], u[5]);
    addEdge(g, u[4], u[5]);
    addEdge(g, u[5], u[4]);
    addEdge(g, u[6], u[1]);
    addEdge(g, u[6], u[9]);
    addEdge(g, u[7], u[8]);
    addEdge(g, u[8], u[7]);
    addEdge(g, u[9], u[6]);
}

void printuser(User u) {
    printf("[%03ld] %20s (%s) | %02d | %5s | %s\n", u.uid, u.name, u.gender, u.age, u.institution, u.city);
}

void searchuserbyuid(Graph *g) {
    clrscr;

    int uid;
    printf("Enter the UID: ");
    scanf("%d", &uid);

    if (g->adjList[uid])
        printuser(*(g->adjList[uid]));
    else
        printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

    printf("\n");
}

void searchuserbyname(Graph *g) {
    clrscr;

    bool found = 0;

    string name;
    printf("Enter the Name: ");
    getchar();
    scanf("%[^\n]s", name);

    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
            printuser(*(g->adjList[i]));
            found = 1;
            break;
        }

    if (!found)
        printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

    printf("\n");
}

void edituserbyuid(Graph *g) {
    clrscr;

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
        printf("Gender: ");
        getchar();
        scanf("%[^\n]s", g->adjList[uid]->gender);
        printf("Institution: ");
        getchar();
        scanf("%[^\n]s", g->adjList[uid]->institution);
        printf("City: ");
        getchar();
        scanf("%[^\n]s", g->adjList[uid]->city);

        printf("Edited.\n");
        printuser(*(g->adjList[uid]));
    } else
        printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

    printf("\n");
}

void edituserbyname(Graph *g) {
    clrscr;

    bool found = 0;

    string name;
    printf("Enter the Name: ");
    getchar();
    scanf("%[^\n]s", name);

    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
            printuser(*(g->adjList[i]));
            printf("\n");

            printf("Enter the new details\n");
            printf("Name: ");
            getchar();
            scanf("%[^\n]s", g->adjList[i]->name);
            printf("Age: ");
            scanf("%d", &g->adjList[i]->age);
            printf("Gender: ");
            getchar();
            scanf("%[^\n]s", g->adjList[i]->gender);
            printf("Institution: ");
            getchar();
            scanf("%[^\n]s", g->adjList[i]->institution);
            printf("City: ");
            getchar();
            scanf("%[^\n]s", g->adjList[i]->city);

            printf("Edited.\n");
            printuser(*(g->adjList[i]));
            found = 1;
            break;
        }

    if (!found)
        printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

    printf("\n");
}

void displayusers(Graph *g) {
    clrscr;

    bool found = 0;
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < g->V; ++i)
        if (g->adjList[i]) {
            if (!found)
                found = 1;
            printuser(*(g->adjList[i]));
        }

    if (!found)
        printf("User Database is Empty!\n");

    printf("--------------------------------------------------------\n");

    printf("\n");
}

void removeuserbyuid(Graph *g, Heap *h) {
    clrscr;

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
        printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

    printf("\n");
}

void removeuserbyname(Graph *g, Heap *h) {
    clrscr;

    bool found = 0;

    string name;
    printf("Enter the Name: ");
    getchar();
    scanf("%[^\n]s", name);

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
        printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

    printf("\n");
}

void displayFriendshipGraph(Graph *g) {
    clrscr;

    for (int i = 0; i < g->V; ++i) {
        if (g->adjList[i]) {
            User *temp = g->adjList[i];
            printf("Friends of %s: ", (temp->name));
            temp = temp->next;
            while (temp) {
                printf("%s", temp->name);
                temp = temp->next;
                if (temp)
                    printf(", ");
            }
            printf("\n");
        }
    }

    printf("\n");
}

void recommendfriend(Graph *g) {}

void checkfriend(Graph *g) {
    clrscr;

    int uid1, uid2;
    printf("Enter the 2 UIDs: ");
    scanf("%d %d", &uid1, &uid2);

    if (g->adjList[uid1] == NULL || g->adjList[uid2] == NULL) {
        printf("ERROR 404: USER(S) NOT FOUND!\n");
        return;
    }

    bool friend12 = 0;
    User *temp = g->adjList[uid1]->next;
    while (temp)
        if (!strcmp(temp->name, g->adjList[uid2]->name)) {
            friend12 = 1;
            break;
        } else {
            temp = temp->next;
        }

    bool friend21 = 0;
    temp = g->adjList[uid2]->next;
    while (temp)
        if (!strcmp(temp->name, g->adjList[uid1]->name)) {
            friend21 = 1;
            break;
        } else {
            temp = temp->next;
        }

    if (friend12 && friend21)
        printf("%s and %s are Mutual Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
    else if (friend12)
        printf("%s considers %s to be a friend.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
    else if (friend21)
        printf("%s considers %s to be a friend.\n", g->adjList[uid2]->name, g->adjList[uid1]->name);
    else
        printf("%s and %s are not Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);

    printf("\n");
}
