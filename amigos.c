#include "amigos.h"

Graph *g;
Heap *h;
int V = 101;
int entries = 15;
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

// Creates a new User Node
// User *createUser(User u) {
//   User *newUser = malloc(sizeof(User));

//   newUser->uid = u.uid;
//   strcpy(newUser->name, u.name);
//   strcpy(newUser->age, u.age);
//   strcpy(newUser->gender, u.gender);
//   strcpy(newUser->email, u.email);
//   strcpy(newUser->job_title, u.job_title);
//   strcpy(newUser->university, u.university);
//   strcpy(newUser->city, u.city);
//   strcpy(newUser->country, u.country);
//   newUser->friendlist = NULL;

//   return newUser;
// }

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

  for (int i = 1; i <= entries; ++i) {
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

    g->userList[g->minUID++] = u;
  }

  // for (int i = 1; i <= entries * 2; ++i) {
  // 	int u = (rand() % entries) + 1;
  // 	int v = (rand() % entries) + 1;

  // 	if (u != v)
  // 		addFriendship(g, *g->userList[u], *g->userList[v]);
  // }

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
  printf("Enter the UID: ");
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
  printf("Enter the UID: ");
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
  printf("Enter the UID: ");
  scanf("%d", &userid);

  if (g->userList[userid].uid) {
    printUser(g->userList[userid]);
    printf("Confirm Delete (y/n)? ");
    char c, buff;
    scanf("%c%c", &buff, &c);
    if (c != 'n') {
      printf("Deleted!\n");
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
void addFriendship(User u, User v) {
  // User *newUser = createUser(v);
  // newUser->friendlist = g->userList[u.uid].friendlist;
  // g->userList[u.uid].friendlist = newUser;
}

void addFriendshipUID() {}
void addFriendshipName() {}

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

  int count[151];

  for (int i = 0; i <= max; ++i)
    count[i] = 0;

  for (int i = 0; i < size; i++)
    count[scores[i].val]++;

  for (int i = 1; i < max; i++)
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
  int score = 0; // max 105

  score += 10 - abs(atoi(u2.age) - atoi(u1.age));

  if (u1.gender != u2.gender)
    score += 10;
  else
    score += 5;

  if (!strcmp(u1.job_title, u2.job_title))
    score += 40;

  if (!strcmp(u1.university, u2.university))
    score += 30;

  if (!strcmp(u1.city, u2.city))
    score += 10;

  if (!strcmp(u1.country, u2.country))
    score += 5;

  return score;
}

void recommendFriendsNewUser() {
  system("clear");

  int userid;
  printf("Enter the UID: ");
  scanf("%d", &userid);

  printf("{XXX}");
  printUser(g->userList[userid]);

  int toAdd;
  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");
    recommendFriendsMenu();
  }

  intidx scores[g->minUID + 1];
  for (int i = 1; i < g->minUID; ++i) {
    scores[i].idx = i;
    scores[i].val = 0;
  }

  for (int i = 1; i < entries; ++i)
    if (userid != i)
      scores[i].val = compatibilityScore(g->userList[userid], g->userList[i]);
    else
      scores[i].val = 0;

  countingSort(scores, entries);

  for (int i = 0; i < 10; ++i) {
    printf("{%03d}", scores[i].val);
    printUser(g->userList[scores[i].idx]);
  }

  for (int i = 0; i < toAdd; ++i) {
    int friendid;
    printf("Enter the UID: ");
    scanf("%d", &friendid);
    if (g->userList[friendid].uid == 0 || friendid >= g->minUID) {
      printf("Invalid UID! Try again\n");
      i--;
    } else {
      addFriendship(g->userList[userid], g->userList[friendid]);
      printf("Added %s as a Friend\n", g->userList[friendid].name);
    }
  }
}

void recommendFriendsExistingUser() {}

void checkFriendshipUID() {
  // system("clear");

  // int uid1, uid2;
  // printf("Enter the 2 UIDs\n");
  // scanf("%d %d", &uid1, &uid2);

  // if (g->userList[uid1].uid == 0 || g->userList[uid2].uid == 0) {
  //   printf("ERROR 404: USER(S) NOT FOUND!\n");
  //   return;
  // }

  // bool friend12 = 0;
  // User *temp = g->userList[uid1].friendlist;
  // while (temp)
  //   if (!strcmp(temp->name, g->userList[uid2].name)) {
  //     friend12 = 1;
  //     break;
  //   } else {
  //     temp = temp->friendlist;
  //   }

  // bool friend21 = 0;
  // temp = g->userList[uid2].friendlist;
  // while (temp)
  //   if (!strcmp(temp->name, g->userList[uid1].name)) {
  //     friend21 = 1;
  //     break;
  //   } else {
  //     temp = temp->friendlist;
  //   }

  // if (friend12 && friend21)
  //   printf("%s and %s are Mutual Friends.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);
  // else if (friend12)
  //   printf("%s considers %s to be a friend.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);
  // else if (friend21)
  //   printf("%s considers %s to be a friend.\n", g->userList[uid2].name,
  //          g->userList[uid1].name);
  // else
  //   printf("%s and %s are not Friends.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);

  // printf("\n");
}

void checkFriendshipName() {
  // system("clear");

  // string name1, name2;
  // printf("Enter the 2 Names\n");
  // gets(name1);
  // gets(name2);

  // int uid1 = 0;
  // int uid2 = 0;

  // for (int i = 0; i < g->V; ++i)
  //   if (uid1 && uid2)
  //     break;
  //   else if (g->userList[i].uid && !strcmp(g->userList[i].name, name1))
  //     uid1 = i;
  //   else if (g->userList[i].uid && !strcmp(g->userList[i].name, name2))
  //     uid2 = i;

  // if (g->userList[uid1].uid == NULL || g->userList[uid2].uid == NULL) {
  //   printf("ERROR 404: USER(S) NOT FOUND!\n");
  //   return;
  // }

  // bool friend12 = 0;
  // User *temp = g->userList[uid1].friendlist;
  // while (temp)
  //   if (!strcmp(temp->name, g->userList[uid2].name)) {
  //     friend12 = 1;
  //     break;
  //   } else {
  //     temp = temp->friendlist;
  //   }

  // bool friend21 = 0;
  // temp = g->userList[uid2].friendlist;
  // while (temp)
  //   if (!strcmp(temp->name, g->userList[uid1].name)) {
  //     friend21 = 1;
  //     break;
  //   } else {
  //     temp = temp->friendlist;
  //   }

  // if (friend12 && friend21)
  //   printf("%s and %s are Mutual Friends.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);
  // else if (friend12)
  //   printf("%s considers %s to be a friend.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);
  // else if (friend21)
  //   printf("%s considers %s to be a friend.\n", g->userList[uid2].name,
  //          g->userList[uid1].name);
  // else
  //   printf("%s and %s are not Friends.\n", g->userList[uid1].name,
  //          g->userList[uid2].name);

  // printf("\n");
}

// Displays the Frienship Network
void displayFriendsAdjacencyList() {
  // system("clear");

  // bool found = 0;

  // printf("-------------------------------------------------------");
  // printf("-------------------------------------------------------");
  // printf("-------------------------------------------------------\n");

  // for (int i = 1; i < g->V; ++i) {
  //   if (g->userList[i].uid) {
  //     if (!found)
  //       found = 1;
  //     User temp = g->userList[i];
  //     printf("Friends of [%03d] %25s: ", temp.uid, temp.name);
  //     temp.friendlist = temp.friendlist;
  //     while (temp.friendlist) {
  //       printf("[%03d]%s", temp.uid, temp.name);
  //       temp.friendlist = temp.friendlist;
  //       if (temp.friendlist)
  //         printf(", ");
  //     }
  //     printf("\n");
  //   }
  // }

  // if (!found)
  //   printf("User Database is Empty!\n");

  // printf("-------------------------------------------------------");
  // printf("-------------------------------------------------------");
  // printf("-------------------------------------------------------\n");

  // printf("\n");
}

//  Writes the Adjacency List for Network Visualization in DOT
void writeFriendshipNetwork() {
  // system("clear");

  // if (entries > 100) {
  //   printf("ERROR: 100+ Nodes in the graph!\n");
  //   printf("Amigos is doing so well that Graphviz doesn't support rendering "
  //          "such a tremendously dense graph.\n");

  //   getchar();
  //   getchar();

  //   displayFriendsMenu();
  // }

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