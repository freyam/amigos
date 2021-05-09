#include "amigos.h"

Graph *g;
Heap *h;
int V = 101;
int entriesImported = 15;
User NULLUSER = {0, "", "", "", "", "", "", "", ""};

bool importRandomData = 0;
bool importCustomData = 1;

// Adds Password Checker
void authorization() {
  string pass;
  gets(pass);
  if (strcmp(pass, "team13")) {
    system("clear");
    printf("403 ACCESS DENIED!\n");
    exit(0);
  }
}

// Initializes the Necessary Functions and Data Structures
void initialize() {
  srand(time(0));

  g = createGraph(V);
  h = createHeap(V);

  if (importRandomData || importCustomData)
    importData(g);
}

// Finds the minimum UID for a new user
int findUID(Heap *h) {
  if (h->count == 0 || g->minUID <= h->arr[0])
    return (g->minUID)++;
  else
    return PopMin(h);
}

// Creates the Friendship Network
Graph *createGraph(int V) {
  Graph *g = malloc(sizeof(Graph));

  g->V = V;
  g->minUID = 1;

  g->userList = malloc(V * sizeof(User));

  for (int i = 0; i < V; i++) {
    g->userList[i] = NULLUSER;
    g->userList[i].friendlist = NULL;
  }

  return g;
}

// Adds a new User to the Friendship Network
void addUser() {
  User u;
  u.uid = findUID(h);
  printf("Enter the details of User [%03d]\n", u.uid);
  printf("Name: ");
  gets(u.name);
  printf("Age: ");
  gets(u.age);
  printf("Gender: ");
  gets(u.gender);
  printf("Email: ");
  gets(u.email);
  printf("Job Title: ");
  gets(u.job_title);
  printf("University: ");
  gets(u.university);
  printf("City: ");
  gets(u.city);
  printf("Country: ");
  gets(u.country);

  g->userList[u.uid] = u;
  g->userList[u.uid].friendlist = NULL;
  printUser(g->userList[u.uid]);
}

// Imports a User Database from UserDatabase.csv
void importData() {
  system("clear");

  char comma = ',';

  string filename;
  if (importRandomData)
    strcpy(filename, "data/RandomUserDatabase.csv");
  else if (importCustomData)
    strcpy(filename, "data/CustomUserDatabase.csv");

  if (access(filename, F_OK))
    system("make import");

  FILE *f = fopen(filename, "r");

  char header[100];
  fscanf(f, "%s", header);

  for (int i = 1; i <= entriesImported; ++i) {
    User u;

    fscanf(f, "%d", &u.uid);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.name);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.gender);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.age);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.email);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.job_title);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.university);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^,]s", u.city);
    fscanf(f, "%c", &comma);
    fscanf(f, "%[^\n]s", u.country);

    g->userList[g->minUID] = u;
    g->userList[g->minUID++].friendlist = NULL;
  }

  bool addRandomFriendships = 0;
  if (addRandomFriendships)
    for (int i = 1; i <= 2 * entriesImported; ++i) {
      int u = (rand() % entriesImported) + 1;
      int v = (rand() % entriesImported) + 1;

      if (u != v)
        addFriendship(u, v);
    }

  fclose(f);
}

// Prints User Information
void printUser(User u) {
  printf("[%03d] %20s | %2s | %1s | %30s | %20s | %20s | %20s | %s\n", u.uid,
         u.name, u.age, u.gender, u.email, u.job_title, u.university, u.city,
         u.country);
}

// Searches a User by UID
void searchUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid)
    printUser(g->userList[userid]);
  else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Searches a User by Name
void searchUserName() {
  system("clear");

  bool found = 0;

  string username;
  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, username)) {
      printUser(g->userList[i]);
      found = 1;
      break;
    }

  if (!found)
    printf("ERROR 404: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Edits User by UID
void editUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid) {
    printUser(g->userList[userid]);
    printf("\n");

    printf("Enter the new details\n");
    printf("Name: ");
    gets(g->userList[userid].name);
    printf("Age: ");
    gets(g->userList[userid].age);
    printf("Gender: ");
    gets(g->userList[userid].gender);
    printf("Email: ");
    gets(g->userList[userid].email);
    printf("Job Title: ");
    gets(g->userList[userid].job_title);
    printf("University: ");
    gets(g->userList[userid].university);
    printf("City: ");
    gets(g->userList[userid].city);
    printf("Country: ");
    gets(g->userList[userid].country);

    printf("Edited.\n");
    printUser(g->userList[userid]);
  } else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Edits User by Name
void editUserName() {
  system("clear");

  bool found = 0;

  string username;
  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, username)) {
      printUser(g->userList[i]);
      printf("\n");

      printf("Enter the new details\n");
      printf("Name: ");
      gets(g->userList[i].name);
      printf("Age: ");
      gets(g->userList[i].age);
      printf("Gender: ");
      gets(g->userList[i].gender);
      printf("Email: ");
      gets(g->userList[i].email);
      printf("Job Title: ");
      gets(g->userList[i].job_title);
      printf("University: ");
      gets(g->userList[i].university);
      printf("City: ");
      gets(g->userList[i].city);
      printf("Country: ");
      gets(g->userList[i].country);

      printf("Edited.\n");
      printUser(g->userList[i]);
      found = 1;
      break;
    }

  if (!found)
    printf("ERROR 404: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Displays the User Database
void displayUserDatabase() {
  system("clear");

  bool found = 0;
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  for (int i = 1; i < g->V; ++i)
    if (g->userList[i].uid) {
      if (!found)
        found = 1;
      printUser(g->userList[i]);
    }

  if (!found)
    printf("User Database is Empty!\n");

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  printf("\n");
  getchar();
  getchar();
}
// Removes User by UID
void removeUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid) {
    printUser(g->userList[userid]);
    printf("Confirm Delete (y/n)? ");
    char c, buff;
    scanf("%c%c", &buff, &c);
    if (c != 'n') {
      printf("Deleted!\n");

      for (int i = 0; i < g->minUID; ++i) {
        if (g->userList[i].uid && g->userList[i].friendlist) {
          bool exists = findFriend(g->userList[i].friendlist, userid);
          if (exists)
            g->userList[i].friendlist = deleteNode(g->userList[i].friendlist, userid);
        }
      }

      insertHeap(h, userid);
      g->userList[userid] = NULLUSER;
      g->userList[userid].friendlist = NULL;

    } else {
      printf("Skipped!\n");
    }
  } else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Removes User by Name
void removeUserName() {
  system("clear");

  bool found = 0;

  string username;
  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, username)) {
      printUser(g->userList[i]);
      printf("Confirm Delete (y/n)? ");
      char c, buff;
      scanf("%c%c", &buff, &c);

      if (c != 'n') {
        printf("Deleted!\n");

        for (int j = 0; j < g->minUID; ++j) {
          if (g->userList[i].uid && g->userList[i].friendlist) {
            bool exists = findFriend(g->userList[i].friendlist, j);
            if (exists)
              g->userList[i].friendlist = deleteNode(g->userList[i].friendlist, j);
          }
        }

        insertHeap(h, i);
        g->userList[i] = NULLUSER;
        g->userList[i].friendlist = NULL;
        found = 1;
      } else {
        printf("Skipped!\n");
      }
      break;
    }

  if (!found)
    printf("ERROR 404: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Adds a Frienship to the Network
void addFriendship(int userid, int friendid) {
  g->userList[userid].friendlist = insertTreeNode(g->userList[userid].friendlist, friendid);
}

void addFriendshipUID() {
  system("clear");

  int userid, friendid;
  printf("Enter the User ID and the Friend ID: ");
  scanf("%d %d", &userid, &friendid);

  if (g->userList[userid].uid && g->userList[friendid].uid) {
    printUser(g->userList[userid]);
    printUser(g->userList[friendid]);

    addFriendship(userid, friendid);

    printf("Added %s as %s\'s Friend.\n",
           g->userList[friendid].name, g->userList[userid].name);
  } else
    printf("EROR 404: USER ID(s) NOT FOUND!\n");

  printf("\n");
}

void addFriendshipName() {
  system("clear");

  bool founduser = 0, foundfriend = 0;
  int userid = 0, friendid = 0;
  string username, friendname;

  printf("Enter the User Name: ");
  gets(username);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, username)) {
      userid = i;
      founduser = 1;
      printUser(g->userList[i]);
      break;
    }

  if (!founduser) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, friendname)) {
      friendid = i;
      foundfriend = 1;
      printUser(g->userList[i]);
      break;
    }

  if (!foundfriend) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }

  addFriendship(userid, friendid);
  printf("Added %s as %s\'s Friend.\n",
         g->userList[friendid].name, g->userList[userid].name);

  printf("\n");
}

void countingSort(intidx scores[], int size) {
  intidx temp[size];
  for (int i = 0; i < size; ++i) {
    temp[i].idx = i;
    temp[i].val = 0;
  }
  int max = scores[0].val;
  for (int i = 1; i < size; i++)
    if (scores[i].val > max)
      max = scores[i].val;

  int count[101];

  for (int i = 0; i <= max; ++i)
    count[i] = 0;

  for (int i = 0; i < size; i++)
    count[scores[i].val]++;

  for (int i = 1; i <= max; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    temp[count[scores[i].val] - 1] = scores[i];
    count[scores[i].val]--;
  }

  for (int i = 0; i < size; i++)
    scores[i] = temp[i];

  for (int low = 0, high = size - 1; low < high; low++, high--) {
    intidx temp = scores[low];
    scores[low] = scores[high];
    scores[high] = temp;
  }
}

void printINTIDXarray(intidx arr[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("[%d] %d ", arr[i].idx, arr[i].val);
  }
  printf("\n");
}

int compatibilityScore(User u1, User u2) {
  int score = 0; // max 100

  score += 10 - abs(atoi(u2.age) - atoi(u1.age));

  if (strcmp(u1.gender, u2.gender))
    score += 10;
  else
    score += 5;

  if (!strcmp(u1.job_title, u2.job_title))
    score += 40;

  if (!strcmp(u1.university, u2.university))
    score += 30;

  if (!strcmp(u1.city, u2.city))
    score += 5;

  if (!strcmp(u1.country, u2.country))
    score += 5;

  return score;
}

void recommendFriendsNewUser() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid == 0) {
    printf("ERROR 404: USER #%d NOT FOUND.", userid);
    return;
  }

  printf("------> ");
  printUser(g->userList[userid]);

  int toAdd;
  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");
    recommendFriendsMenu();
  }

  intidx scores[g->minUID];
  for (int i = 0; i < g->minUID; ++i) {
    scores[i].idx = i + 1;

    if (i + 1 != userid)
      scores[i].val = compatibilityScore(g->userList[userid], g->userList[i + 1]);
    else
      scores[i].val = 0;
  }

  // printINTIDXarray(scores, g->minUID);
  countingSort(scores, g->minUID);
  // printINTIDXarray(scores, g->minUID);

  for (int i = 0; i < 10; ++i) {
    printf("%03d%% -> ", scores[i].val);
    printUser(g->userList[scores[i].idx]);
  }

  for (int i = 0; i < toAdd; ++i) {
    int friendid;
    printf("Enter the User ID: ");
    scanf("%d", &friendid);

    if (g->userList[friendid].uid == 0 || friendid >= g->minUID) {
      printf("Invalid UID! Try again\n");
      i--;
    } else {
      addFriendship(userid, friendid);
      printf("Added %s as a Friend\n", g->userList[friendid].name);
    }
  }
}

void recommendFriendsExistingUser() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid == 0) {
    printf("ERROR 404: USER #%d NOT FOUND.\n", userid);
    return;
  }

  printf("------> ");
  printUser(g->userList[userid]);

  int toAdd;
  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");
    recommendFriendsMenu();
  }

  if (g->userList[userid].friendlist == NULL) {
    printf("%s has no friends.\n", g->userList[userid].name);
    printf("Treat %s as a New User (y/n)? ", g->userList[userid].name);
    char c, buff;
    scanf("%c%c", &buff, &c);
    if (c != 'n') {
      recommendFriendsNewUser();
    } else {
      printf("Skipped!\n");
    }
    return;
  }

  Queue *q = createQueue(g->minUID);
  Queue *newFriends = createQueue(toAdd);

  bool visited[g->minUID];
  bool alreadyfriend[g->minUID];
  for (int i = 0; i < g->minUID; ++i)
    alreadyfriend[i] = visited[i] = 0;

  visited[userid] = alreadyfriend[userid] = 1;

  firstPass(g->userList[userid].friendlist, q, alreadyfriend);
  for (int i = 0; i < g->minUID; ++i)
    visited[i] = alreadyfriend[i];

  int added = 0;
  while (!isEmpty(q) && added < toAdd) {
    int fid = dequeue(q);
    if (!alreadyfriend[fid]) {
      added++;
      enqueue(newFriends, fid);
    }

    treeNode *temp = g->userList[fid].friendlist;
    if (temp == NULL)
      continue;
    else
      firstPass(temp, q, visited);
  }

  printf("\n");
  printQueue(newFriends);
}

void checkFriendshipUID() {
  system("clear");

  int userid, friendid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid == 0) {
    printf("ERROR 404: USER #%03d NOT FOUND!\n", userid);
    return;
  }

  printf("Enter the Friend ID: ");
  scanf("%d", &friendid);

  if (g->userList[friendid].uid == 0) {
    printf("ERROR 404: USER #%03d NOT FOUND!\n", friendid);
    return;
  }

  bool friend12 = findFriend(g->userList[userid].friendlist, friendid);
  bool friend21 = findFriend(g->userList[friendid].friendlist, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", g->userList[userid].name,
           g->userList[friendid].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", g->userList[userid].name,
           g->userList[friendid].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", g->userList[friendid].name,
           g->userList[userid].name);
  else
    printf("%s and %s are not Friends.\n", g->userList[userid].name,
           g->userList[friendid].name);

  printf("\n");
}

void checkFriendshipName() {
  system("clear");

  bool founduser = 0, foundfriend = 0;
  int userid = 0, friendid = 0;
  string username, friendname;

  printf("Enter the User Name: ");
  gets(username);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, username)) {
      userid = i;
      founduser = 1;
      printUser(g->userList[i]);
      break;
    }

  if (!founduser) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);

  for (int i = 0; i < g->V; ++i)
    if (g->userList[i].uid && !strcmp(g->userList[i].name, friendname)) {
      friendid = i;
      foundfriend = 1;
      printUser(g->userList[i]);
      break;
    }

  if (!foundfriend) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }

  bool friend12 = findFriend(g->userList[userid].friendlist, friendid);
  bool friend21 = findFriend(g->userList[friendid].friendlist, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", g->userList[userid].name,
           g->userList[friendid].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", g->userList[userid].name,
           g->userList[friendid].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", g->userList[friendid].name,
           g->userList[userid].name);
  else
    printf("%s and %s are not Friends.\n", g->userList[userid].name,
           g->userList[friendid].name);

  printf("\n");
}

void printFriendlist(treeNode *root) {
  if (root != NULL) {
    printFriendlist(root->leftchild);
    printf("%s | ", g->userList[root->friendid].name);
    printFriendlist(root->rightchild);
  }
}

// Displays the Frienship Network
void displayFriendsAdjacencyList() {
  system("clear");

  bool found = 0;

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  for (int i = 1; i < g->V; ++i) {
    if (g->userList[i].uid) {
      if (!found)
        found = 1;

      printf("Friends of [%03d] %25s: ", g->userList[i].uid, g->userList[i].name);

      if (g->userList[i].friendlist)
        printFriendlist(g->userList[i].friendlist);
      else
        printf("NULL");

      printf("\n");
    }
  }

  if (!found)
    printf("User Database is Empty!\n");

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  printf("\n");
}

//  Writes the Adjacency List for Network Visualization in DOT
void writeFriendshipNetwork() {
  system("clear");

  if (g->minUID > 100) {
    printf("ERROR: 100+ Nodes in the graph!\n");
    printf("Amigos is doing so well that Graphviz doesn't support rendering "
           "such a tremendously dense graph.\n");

    getchar();
    getchar();

    displayFriendsMenu();
  }

  // FILE *f = fopen("graph/graphviz.dot", "w");

  // fprintf(f, "digraph AmigosFriendNetwork {\n");
  // fprintf(f, "\tnode [fontname=\"Consolas\", shape=oval, style=filled, "
  //            "color=\".7 .3 1.0\"];\n");

  // for (int i = 1; i < g->V; ++i) {
  //   if (g->userList[i]) {
  //     User temp = g->userList[i];

  //     fprintf(f, "\t\"%s\"", temp->name);
  //     temp = temp->friendlist;

  //     if (temp)
  //       fprintf(f, " -> ");

  //     while (temp) {
  //       fprintf(f, "\"%s\"", temp->name);
  //       temp = temp->friendlist;
  //       if (temp)
  //         fprintf(f, " -> ");
  //     }

  //     fprintf(f, "\n");
  //   }
  // }

  // fprintf(f, "}");
  // fclose(f);
}

void ViewFriendshipNetwork() {
  // writeFriendshipNetwork(g);
  // system("dot -Tpng graph/graphviz.dot -o graph/friendship-network.png && xdg-open graph/friendship-network.png");
}