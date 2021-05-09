#include "amigos.h"

FriendNetwork *network;                              // The core Network Data Structure
Heap *token;                                         // The core Token Counter
User NULLUSER = {0, "", "", "", "", "", "", "", ""}; // A NULL User

int V;       // The Total Number of Vertices
int entries; // The Total Number of Entries to Import

bool importRandomData = 1; // Toggle Importing API-generated Random User Date
bool importCustomData = 0; // Toggle Importing Custom User-generated User Data

// Adds Password Checker
void authentication() {
  string pass;
  scanf("%s", pass);

  if (strcmp(pass, "team13")) {
    system("clear");
    printf("[ERROR #403] ACCESS DENIED!\n");
    exit(EXIT_SUCCESS);
  }
}

// Initializes the Necessary Functions and Data Structures
void initialize() {
  srand(time(0));

  V = 101;
  entries = 20;

  network = createGraph(V);
  token = createHeap(V);

  if (importRandomData || importCustomData)
    importData(); // Import Data from data Folder
}

// Finds the minimum UID for a new user from a Min Heap
int findUID() {
  if (token->count == 0 || network->minUID <= token->arr[0])
    return (network->minUID)++;
  else
    return PopMin(token);
}

// Creates the Friendship Network
FriendNetwork *createGraph(int V) {
  FriendNetwork *network = malloc(sizeof(FriendNetwork));

  network->V = V;
  network->minUID = 1;

  network->userList = malloc(V * sizeof(User));

  for (int i = 0; i < V; i++) {
    network->userList[i] = NULLUSER;
    network->userList[i].friend_list = NULL;
  }

  return network;
}

// Adds a new User to the Friendship Network
void addUser() {
  User u;

  u.uid = findUID();
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

  network->userList[u.uid] = u;
  network->userList[u.uid].friend_list = NULL;

  printUser(network->userList[u.uid]);
}

// Imports a User Database from The API-generated or User-generated User Database
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

    network->userList[network->minUID] = u;
    network->userList[network->minUID++].friend_list = NULL;
  }

  bool addRandomFriendships = 1;
  if (addRandomFriendships)
    for (int i = 1; i <= 2 * entries; ++i) {
      int u = (rand() % entries) + 1;
      int v = (rand() % entries) + 1;

      if (u != v)
        addFriendship(u, v);
    }

  fclose(f);
}

// Pretty Prints User Information
void printUser(User u) {
  printf("[%03d] %20s | %2s | %1s | %40s | %50s | %40s | %s\n",
         u.uid, u.name, u.age, u.gender, u.job_title, u.university, u.city, u.country);
}

// Searches a User by UID
// by O(1) Array Lookup
void searchUserUID() {
  system("clear");

  int userid;

  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid)
    printUser(network->userList[userid]);
  else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Searches a User by Name
// by O(V) Array Traversal
void searchUserName() {
  system("clear");

  bool found = 0;

  string username;

  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, username)) {
      printUser(network->userList[i]);
      found = 1;
      break;
    }

  if (!found)
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Edits User by UID
// by O(1) Array Lookup
void editUserUID() {
  system("clear");

  int userid;

  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid) {
    printUser(network->userList[userid]);
    printf("\n");

    printf("Enter the New Details\n");
    printf("Name: ");
    gets(network->userList[userid].name);
    printf("Age: ");
    gets(network->userList[userid].age);
    printf("Gender: ");
    gets(network->userList[userid].gender);
    printf("Email: ");
    gets(network->userList[userid].email);
    printf("Job Title: ");
    gets(network->userList[userid].job_title);
    printf("University: ");
    gets(network->userList[userid].university);
    printf("City: ");
    gets(network->userList[userid].city);
    printf("Country: ");
    gets(network->userList[userid].country);

    printf("Edited.\n");

    printUser(network->userList[userid]);
  } else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Edits User by Name
// by O(V) Array Traversal
void editUserName() {
  system("clear");

  bool found = 0;

  string username;

  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, username)) {
      printUser(network->userList[i]);
      printf("\n");

      printf("Enter the New Details\n");
      printf("Name: ");
      gets(network->userList[i].name);
      printf("Age: ");
      gets(network->userList[i].age);
      printf("Gender: ");
      gets(network->userList[i].gender);
      printf("Email: ");
      gets(network->userList[i].email);
      printf("Job Title: ");
      gets(network->userList[i].job_title);
      printf("University: ");
      gets(network->userList[i].university);
      printf("City: ");
      gets(network->userList[i].city);
      printf("Country: ");
      gets(network->userList[i].country);

      printf("Edited.\n");

      printUser(network->userList[i]);

      found = 1;
      break;
    }

  if (!found)
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Displays the User Database
void displayUserDatabase() {
  system("clear");

  bool found = 0;

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  for (int i = 1; i < network->V; ++i)
    if (network->userList[i].uid) {
      if (!found)
        found = 1;
      printUser(network->userList[i]);
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

// Removes User by UID and Refreshes the Respective Friendlists
// by O(1) Array Lookup and O(VlogV) AVL Deletion of Node
void removeUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid) {
    printUser(network->userList[userid]);

    printf("Confirm Delete (y/n)? ");

    char c, buff;
    scanf("%c%c", &buff, &c);

    if (c != 'n') {
      printf("Deleted!\n");

      for (int i = 0; i < network->minUID; ++i) {
        if (network->userList[i].uid && network->userList[i].friend_list) {
          bool exists = findFriend(network->userList[i].friend_list, userid);

          if (exists)
            network->userList[i].friend_list = deleteNode(network->userList[i].friend_list, userid);
        }
      }

      insertHeap(token, userid); // to Insert Freed UID to Heap.

      network->userList[userid] = NULLUSER;
      network->userList[userid].friend_list = NULL;
    } else {
      printf("Skipped!\n");
    }
  } else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}

// Removes User by Name and Refreshes the Respective Friendlists
// by O(V) Array Traversal and O(VlogV) AVL Deletion of Node
void removeUserName() {
  system("clear");

  bool found = 0;

  string username;
  printf("Enter the Name: ");
  gets(username);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, username)) {
      printUser(network->userList[i]);

      printf("Confirm Delete (y/n)? ");

      char c, buff;
      scanf("%c%c", &buff, &c);

      if (c != 'n') {
        printf("Deleted!\n");

        for (int j = 0; j < network->minUID; ++j) {
          if (network->userList[i].uid && network->userList[i].friend_list) {
            bool exists = findFriend(network->userList[i].friend_list, j);

            if (exists)
              network->userList[i].friend_list = deleteNode(network->userList[i].friend_list, j);
          }
        }

        insertHeap(token, i); // to Insert Freed UID to Heap.

        network->userList[i] = NULLUSER;
        network->userList[i].friend_list = NULL;

        found = 1;
      } else {
        printf("Skipped!\n");
      }
      break;
    }

  if (!found)
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}

// Adds a Frienship to the Network
// by O(logV) AVL Insertion of a Node
void addFriendship(int userid, int friend_id) {
  network->userList[userid].friend_list =
      insertTreeNode(network->userList[userid].friend_list, friend_id);
}

// Adds a Frienship to the Network (User Input: 2 UIDs)
// by O(1) Array Lookup and O(logV) AVL Insertion of a Node
void addFriendshipUID() {
  system("clear");

  int userid, friend_id;
  printf("Enter the User ID and the Friend ID: ");
  scanf("%d %d", &userid, &friend_id);

  if (network->userList[userid].uid && network->userList[friend_id].uid) {
    printUser(network->userList[userid]);
    printUser(network->userList[friend_id]);

    addFriendship(userid, friend_id);

    printf("Added %s as %s\'s Friend.\n",
           network->userList[friend_id].name, network->userList[userid].name);
  } else
    printf("EROR 404: USER ID(s) NOT FOUND!\n");

  printf("\n");
}

// Adds a Frienship to the Network (User Input: 2 Names)
// by O(V) Array Lookup and O(logV) AVL Insertion of a Node
void addFriendshipName() {
  system("clear");

  bool founduser = 0, foundfriend = 0;
  int userid = 0, friend_id = 0;
  string username, friendname;

  printf("Enter the User Name: ");
  gets(username);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, username)) {
      userid = i;
      founduser = 1;

      printUser(network->userList[i]);

      break;
    }

  if (!founduser) {
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, friendname)) {
      friend_id = i;
      foundfriend = 1;

      printUser(network->userList[i]);

      break;
    }

  if (!foundfriend) {
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }

  addFriendship(userid, friend_id);
  printf("Added %s as %s\'s Friend.\n",
         network->userList[friend_id].name, network->userList[userid].name);

  printf("\n");
}

// Sorts the Compatibility Scores in Non-Increasing Order
// by O(V) Key Lookup (small integers)
void countingSort(intx scores[], int size) {
  intx temp[size];

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
    intx temp = scores[low];
    scores[low] = scores[high];
    scores[high] = temp;
  }
}

// Prints the INTX Array (for debugging)
void printINTXArray(intx arr[], int size) {
  for (int i = 0; i < size; ++i)
    printf("[%d] %d ", arr[i].idx, arr[i].val);

  printf("\n");
}

// Calculates the Compatibility Score between 2 Users on the basis of their Metadata
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

/*
[Core Function] Recommend Friends to New Users

Algorithm Breakdown
Generates a Array consisting of the Compatibility Scores
with all the Users in the Database.
Sorts the Score Array using Counting Sort (O(V + K) where K = 100)
in Non-Increasing Order.
Traverse through the first 10 Users in the Sorted Score Array and
suggest Friends.
*/
void recommendFriendsNewUser() {
  system("clear");

  int userid;

  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid == 0) {
    printf("[ERROR #404]: USER #%d NOT FOUND.", userid);
    return;
  }

  printf("------> ");
  printUser(network->userList[userid]);

  int toAdd;

  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");
    recommendFriendsMenu();
  }

  intx scores[network->minUID];
  for (int i = 0; i < network->minUID; ++i) {
    scores[i].idx = i + 1;

    if (i + 1 != userid)
      scores[i].val =
          compatibilityScore(network->userList[userid], network->userList[i + 1]);
    else
      scores[i].val = 0;
  }

  countingSort(scores, network->minUID);

  for (int i = 0; i < 10; ++i) {
    printf("%03d%% -> ", scores[i].val);
    printUser(network->userList[scores[i].idx]);
  }

  for (int i = 0; i < toAdd; ++i) {
    int friend_id;

    printf("Enter the User ID: ");
    scanf("%d", &friend_id);

    if (network->userList[friend_id].uid == 0 || friend_id >= network->minUID) {
      printf("Invalid UID! Try again\n");

      i--;
    } else {
      addFriendship(userid, friend_id);

      printf("Added %s as a Friend\n", network->userList[friend_id].name);
    }
  }
}

/*
[Core Function] Recommend Friends to Existing Users

Algorithm Breakdown
Generate 2 Queues to store Current Friends and Recommended Friends
SinglePass() -> Marks the Current Friends as Visited.
Run a Breadth First Traversal on the Friendlist (A AVL Tree) and
update the Queues accordingly.
By the Level order Binary Tree Traversing approach, BFS recommends
the 1st Common Friends > 2nd Common Friends > 3rd Common Friends ...
Traverse through the first toAdd Users in the Queue and suggest Friends.
*/
void recommendFriendsExistingUser() {
  system("clear");

  int userid;

  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid == 0) {
    printf("[ERROR #404]: USER #%d NOT FOUND.\n", userid);

    return;
  }

  printUser(network->userList[userid]);

  int toAdd;

  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");

    recommendFriendsMenu();
  }

  if (network->userList[userid].friend_list == NULL) {
    printf("%s has no friends.\n", network->userList[userid].name);
    printf("Treat %s as a New User (y/n)? ", network->userList[userid].name);

    char c, buff;
    scanf("%c%c", &buff, &c);

    if (c != 'n')
      recommendFriendsNewUser();
    else
      printf("Skipped!\n");

    return;
  }

  Queue *friendstream = createQueue(network->minUID); // Queue to run BFS on
  Queue *recommendedFriends = createQueue(toAdd);     // Queue to store the Recommended Friends

  bool visited[network->minUID];       // Bool Array to track Visited Users
  bool alreadyfriend[network->minUID]; // Bool Array to store Current Friends

  for (int i = 0; i < network->minUID; ++i)
    alreadyfriend[i] = visited[i] = 0;

  visited[userid] = alreadyfriend[userid] = 1; // Flag the Current User so we don't recommend the User itself

  singlePass(network->userList[userid].friend_list, friendstream, alreadyfriend); // Traverse through the Friendlist once and Fill the Queue Accordingly

  for (int i = 0; i < network->minUID; ++i)
    visited[i] = alreadyfriend[i];

  int added = 0;

  while (!isEmpty(friendstream) && added < toAdd) {
    int fid = dequeue(friendstream);

    if (!alreadyfriend[fid]) { // if "fid" isn't already a friend of User, add it to the Recommended Users
      added++;

      enqueue(recommendedFriends, fid);
    }

    treeNode *temp = network->userList[fid].friend_list; // Add all the Friends of the Dequeued Friend

    if (temp == NULL)
      continue;
    else
      singlePass(temp, friendstream, visited); // Traverse through the Friendlist once again and Fill the Queue Accordingly
  }

  printf("\n");

  if (isEmpty(friendstream)) {
    printf("No Friend Recommendations!");
  } else {
    for (int i = friendstream->front; i < friendstream->rear + 1; ++i)
      printUser(network->userList[friendstream->items[i]]);

    printf("\n");
  }

  for (int i = 0; i < toAdd; ++i) {
    int friend_id;

    printf("Enter the User ID: ");
    scanf("%d", &friend_id);

    if (network->userList[friend_id].uid == 0 || friend_id >= network->minUID) {
      printf("Invalid UID! Try again\n");

      i--;
    } else {
      addFriendship(userid, friend_id);

      printf("Added %s as a Friend\n", network->userList[friend_id].name);
    }
  }
}

// Checks whether 2 Users are Friends (User Input: UIDs)
// by O(1) Array Lookup and O(logV) AVL Tree Search
void checkFriendshipUID() {
  system("clear");

  int userid, friend_id;

  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (network->userList[userid].uid == 0) {
    printf("[ERROR #404]: USER #%03d NOT FOUND!\n", userid);

    return;
  }

  printf("Enter the Friend ID: ");
  scanf("%d", &friend_id);

  if (network->userList[friend_id].uid == 0) {
    printf("[ERROR #404]: USER #%03d NOT FOUND!\n", friend_id);

    return;
  }

  bool friend12; // Is User 2 a friend of User 1?
  friend12 = findFriend(network->userList[userid].friend_list, friend_id);

  bool friend21; // Is User 1 a friend of User 2?
  friend21 = findFriend(network->userList[friend_id].friend_list, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", network->userList[userid].name,
           network->userList[friend_id].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", network->userList[userid].name,
           network->userList[friend_id].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", network->userList[friend_id].name,
           network->userList[userid].name);
  else
    printf("%s and %s are not Friends.\n", network->userList[userid].name,
           network->userList[friend_id].name);

  printf("\n");
}

// Checks whether 2 Users are Friends (User Input: Names)
// by O(V) Array Traversal and O(logV) AVL Tree Search
void checkFriendshipName() {
  system("clear");

  bool founduser = 0, foundfriend = 0;
  int userid = 0, friend_id = 0;
  string username, friendname;

  printf("Enter the User Name: ");
  gets(username);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, username)) {
      userid = i;
      founduser = 1;

      printUser(network->userList[i]);

      break;
    }

  if (!founduser) {
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);

  for (int i = 0; i < network->V; ++i)
    if (network->userList[i].uid && !strcmp(network->userList[i].name, friendname)) {
      friend_id = i;
      foundfriend = 1;

      printUser(network->userList[i]);

      break;
    }

  if (!foundfriend) {
    printf("[ERROR #404]: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }

  bool friend12; // Is User 2 a friend of User 1?
  friend12 = findFriend(network->userList[userid].friend_list, friend_id);

  bool friend21; // Is User 1 a friend of User 2?
  friend21 = findFriend(network->userList[friend_id].friend_list, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", network->userList[userid].name,
           network->userList[friend_id].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", network->userList[userid].name,
           network->userList[friend_id].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", network->userList[friend_id].name,
           network->userList[userid].name);
  else
    printf("%s and %s are not Friends.\n", network->userList[userid].name,
           network->userList[friend_id].name);

  printf("\n");
}

// Prints the Friendlist of a User
// by O(V) AVL Tree PreOrder recursive traversal
void printFriendlist(treeNode *root) {
  if (root != NULL) {
    printFriendlist(root->left_child);

    printf("%s | ", network->userList[root->friend_id].name);

    printFriendlist(root->right_child);
  }
}

// Displays the Frienship Network in an Adjacency List format
void displayFriendshipNetwork() {
  system("clear");

  bool found = 0;

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  for (int i = 1; i < network->V; ++i) {
    if (network->userList[i].uid) {
      if (!found)
        found = 1;

      printf("Friends of [%03d] %25s: ", network->userList[i].uid, network->userList[i].name);

      if (network->userList[i].friend_list)
        printFriendlist(network->userList[i].friend_list);
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

// Writes the Friendlist of a User into the the Graphviz DOT Source
// by O(V) AVL Tree PreOrder recursive traversal
void writeFriendlist(treeNode *root, FILE *f) {
  if (root != NULL) {
    writeFriendlist(root->left_child, f);

    fprintf(f, " -> \"%s\"", network->userList[root->friend_id].name);

    writeFriendlist(root->right_child, f);
  }
}

//  Writes the Adjacency List for Network Visualization
// into the the Graphviz DOT Source
void writeFriendshipNetwork() {
  system("clear");

  if (network->minUID > 100) {
    printf("ERROR: 100+ Nodes in the graph!\n");
    printf("Amigos is doing so well that Graphviz doesn't support rendering "
           "such a tremendously dense graph.\n");

    getchar();
    getchar();

    displayFriendsMenu();
  }

  FILE *f = fopen("graph/graphviz.dot", "w");

  fprintf(f, "digraph FriendNetwork {\n");

  fprintf(f, "\tnode [fontname=\"Consolas\", shape=oval, style=filled, color=\".7 .4 1.0\"];\n");
  fprintf(f, "\tlabel = \"Amigos Friendship Network\";\n");
  fprintf(f, "\tlabelloc = \"t\";\n");
  fprintf(f, "\tfontsize  = 30;\n");
  fprintf(f, "\tfontname  = \"Consolas\";\n\n");

  for (int i = 1; i < network->V; ++i) {
    if (network->userList[i].uid) {
      fprintf(f, "\t\"%s\"", network->userList[i].name);

      if (network->userList[i].friend_list)
        writeFriendlist(network->userList[i].friend_list, f);

      fprintf(f, "\n");
    }
  }

  fprintf(f, "}");

  fclose(f);
}

// Renders the Graphviz DOT Source Graph
void ViewFriendshipNetwork() {
  writeFriendshipNetwork(network);

  system("dot -Tpng graph/graphviz.dot -o graph/friendship-network.png && xdg-open graph/friendship-network.png");
}