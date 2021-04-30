#ifndef FRIENDSBOOK
#define FRIENDSBOOK

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

// Queue Functions
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

Graph *createGraph(int);
void addEdge(Graph *, User, User);

User *createUser(User);
void printUser(User);
void adduser(Graph *);     // TODO
void searchuser(Graph *);  // TODO
void edituser(Graph *);    // TODO
void displayuser(Graph *); // TODO
void removeuser(Graph *);  // TODO

void recommendfriend();    // TODO
void displayfriendgraph(); // TODO
void checkfriend();        // TODO

void quit();

#endif
