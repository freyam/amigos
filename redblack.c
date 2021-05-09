#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void banner();
void authorization();
void mainMenu();
void userMenu();
void friendMenu();
void addFriendMenu();
void checkFriendMenu();
void ViewFriendShipNetwork();
void recommendFriendsMenu();
void searchUserMenu();
void editUserMenu();
void removeUserMenu();
void displayFriendsMenu();
void quit();
void importData();
void ViewFriendshipNetwork();
void recommendFriendsNewUser();

struct Heap {
  int *arr;
  int count;
  int capacity;
};
struct Heap *createHeap(int capacity) {
  struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));

  h->count = 0;
  h->capacity = capacity;
  h->arr = (int *)malloc(capacity * sizeof(int));
  return h;
}
void heapify_bottom_top(struct Heap *h, int index) {
  int temp;
  int parent_node = (index - 1) / 2;

  if (h->arr[parent_node] > h->arr[index]) {
    temp = h->arr[parent_node];
    h->arr[parent_node] = h->arr[index];
    h->arr[index] = temp;
    heapify_bottom_top(h, parent_node);
  }
}
void heapify_top_bottom(struct Heap *h, int parent_node) {
  int left = parent_node * 2 + 1;
  int right = parent_node * 2 + 2;
  int min;
  int temp;

  if (left >= h->count || left < 0)
    left = -1;
  if (right >= h->count || right < 0)
    right = -1;

  if (left != -1 && h->arr[left] < h->arr[parent_node])
    min = left;
  else
    min = parent_node;
  if (right != -1 && h->arr[right] < h->arr[min])
    min = right;

  if (min != parent_node) {
    temp = h->arr[min];
    h->arr[min] = h->arr[parent_node];
    h->arr[parent_node] = temp;

    heapify_top_bottom(h, min);
  }
}
void insertHeap(struct Heap *h, int key) {
  if (h->count < h->capacity) {
    h->arr[h->count] = key;
    heapify_bottom_top(h, h->count);
    h->count++;
  }
}

int PopMin(struct Heap *h) {
  int pop;
  if (h->count == 0) {
    printf("\nHeap is Empty\n");
    return -1;
  }
  pop = h->arr[0];
  h->arr[0] = h->arr[h->count - 1];
  h->count--;
  heapify_top_bottom(h, 0);
  return pop;
}
int minUID = 1;
int findUID(struct Heap *h) {
  if (h->count == 0 || minUID <= h->arr[0])
    return (minUID)++;
  else
    return PopMin(h);
}

typedef char string[50];
#define gets(s) \
  getchar();    \
  scanf("%[^\n]s", s);
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
  struct Node *RootUser;
};
void printUser(struct User u) {
  printf("[%03d] %20s | %2s | %1s | %30s | %20s | %20s | %20s | %s\n", u.uid,
         u.name, u.age, u.gender, u.email, u.job_title, u.university, u.city,
         u.country);
}

struct Node {
  int UserID;          // UserID
  int color;           // 1-RED, 0-BLACK
  struct Node *parent; // parent
  struct Node *right;  // right-child
  struct Node *left;   // left child
};
struct User NULLUSER = {0, "", "", "", "", "", "", "", ""};

struct User vertex[1000000];
struct User reversevertex[1000000];
bool exist[1000000] = {false};

int BLACK = 0;
int RED = 1;
struct Node *FindUncle(struct Node *temp) {
  // If no parent or grandparent, then no uncle
  if ((temp->parent == NULL) || (temp->parent->parent == NULL)) {
    return NULL;
  }

  if (temp->parent->left == temp) {
    // uncle on right
    return temp->parent->parent->right;
  } else {
    // uncle on left
    return temp->parent->parent->left;
  }
}
struct Node *FindSibling(struct Node *temp) {
  // sibling null if no parent
  if (temp->parent == NULL)
    return NULL;

  if (temp->parent->left == temp)
    return temp->parent->right;

  return temp->parent->left;
}
void MoveDown(struct Node *temp, struct Node *nParent) {
  if (temp->parent != NULL) {
    if (temp->parent->left == temp) {
      temp->parent->left = nParent;
    } else {
      temp->parent->right = nParent;
    }
  }
  nParent->parent = temp->parent;
  temp->parent = nParent;
}
bool HasRedChild(struct Node *temp) {
  return ((temp->left != NULL && temp->left->color == RED) || (temp->right != NULL && temp->right->color == RED));
}
struct Node *LeftRotate(struct Node *Head, struct Node *x) {
  // new parent will be node's right child
  struct Node *nParent = x->right;

  // update root if current node is root
  if (x == Head)
    Head = nParent;

  MoveDown(x, nParent);

  // connect x with new parent's left element
  x->right = nParent->left;

  // connect new parent's left element with node
  // if it is not null
  if (nParent->left != NULL)
    nParent->left->parent = x;

  // connect new parent with x
  nParent->left = x;

  return Head;
}
struct Node *RightRotate(struct Node *Head, struct Node *x) {
  // new parent will be node's left child
  struct Node *nParent = x->left;

  // update root if current node is root
  if (x == Head)
    Head = nParent;

  MoveDown(x, nParent);

  // connect x with new parent's right element
  x->left = nParent->right;

  // connect new parent's right element with node
  // if it is not null
  if (nParent->right != NULL)
    nParent->right->parent = x;

  // connect new parent with x
  nParent->right = x;

  return Head;
}
void SwapColors(struct Node *x1, struct Node *x2) {
  int temp;
  temp = x1->color;
  x1->color = x2->color;
  x2->color = temp;
}
void SwapValues(struct Node *u, struct Node *v) {
  int temp;
  temp = u->UserID;
  u->UserID = v->UserID;
  v->UserID = temp;
}
struct Node *Restructure(struct Node *Head, struct Node *pt) {
  struct Node *parent_pt = NULL;
  struct Node *grand_parent_pt = NULL;

  while ((pt != Head) && (pt->color != 0) && (pt->parent->color == RED)) {
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    /*Case : A
			Parent of pt is left child
			of Grand-parent of pt
		*/
    if (parent_pt == grand_parent_pt->left) {

      struct Node *uncle_pt = grand_parent_pt->right;

      /*Case : 1
				The uncle of pt is also RED
				Only Recoloring required
			*/
      if (uncle_pt != NULL && uncle_pt->color == RED) {
        grand_parent_pt->color = RED;
        parent_pt->color = 0;
        uncle_pt->color = 0;
        pt = grand_parent_pt;
      }

      else {

        /*Case : 2
					pt is right child of its parent
					Left-rotation required
				*/
        if (pt == parent_pt->right) {
          Head = LeftRotate(Head, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        /*Case : 3
					pt is left child of its parent
					Right-rotation required
				*/
        Head = RightRotate(Head, grand_parent_pt);
        int t = parent_pt->color;
        parent_pt->color = grand_parent_pt->color;
        grand_parent_pt->color = t;
        pt = parent_pt;
      }
    }

    /*Case : B
			Parent of pt is right child of Grand-parent of pt
		*/
    else {
      struct Node *uncle_pt = grand_parent_pt->left;

      /*Case : 1
				The uncle of pt is also RED
				Only Recoloring required
			*/
      if ((uncle_pt != NULL) && (uncle_pt->color == 1)) {
        grand_parent_pt->color = 1;
        parent_pt->color = 0;
        uncle_pt->color = 0;
        pt = grand_parent_pt;
      } else {
        /*Case : 2
					pt is left child of its parent
					Right-rotation required
				*/

        if (pt == parent_pt->left) {
          Head = RightRotate(Head, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }

        /*Case : 3
					pt is right child of its parent
					Left-rotation required
				*/
        Head = LeftRotate(Head, grand_parent_pt);

        int t = parent_pt->color;
        parent_pt->color = grand_parent_pt->color;
        grand_parent_pt->color = t;
        pt = parent_pt;
      }
    }
  }

  Head->color = 0;

  return Head;
}
struct Node *FixRedRed(struct Node *Head, struct Node *x) {
  // if x is root color it black and return
  if (x == Head) {
    x->color = 0;
    return Head;
  }

  // initialize parent, grandparent, uncle
  struct Node *parent1 = x->parent;
  struct Node *grandparent = parent1->parent;
  struct Node *uncle1 = FindUncle(x);

  if (parent1->color != 0) {
    if (uncle1 != NULL && uncle1->color == RED) {
      // uncle red, perform recoloring and recurse
      parent1->color = 0;
      uncle1->color = 0;
      grandparent->color = RED;
      Head = FixRedRed(Head, grandparent);
    } else {
      // Else perform LR, LL, RL, RR
      if (parent1->parent->left == parent1) {
        if (x->parent->left == x) {
          // for left right
          SwapColors(parent1, grandparent);
        } else {
          Head = LeftRotate(Head, parent1);
          SwapColors(x, grandparent);
        }
        // for left left and left right
        Head = RightRotate(Head, grandparent);
      } else {
        if (x->parent->left == x) {
          // for right left
          Head = RightRotate(Head, parent1);
          SwapColors(x, grandparent);
        } else {
          SwapColors(parent1, grandparent);
        }

        // for right right and right left
        Head = LeftRotate(Head, grandparent);
      }
    }
  }
  return Head;
}
struct Node *Successor(struct Node *x) {
  struct Node *temp = x;

  while (temp->left != NULL)
    temp = temp->left;

  return temp;
}
struct Node *RBTreplace(struct Node *x) {
  // when node have 2 children
  if (x->left != NULL && x->right != NULL)
    return Successor(x->right);

  // when leaf
  if (x->left == NULL && x->right == NULL)
    return NULL;

  // when single child
  if (x->left != NULL)
    return x->left;
  else
    return x->right;
}
struct Node *FixDoubleBlack(struct Node *Head, struct Node *x) {
  if (x == Head)
    // Reached root
    return Head;

  struct Node *sibling1 = FindSibling(x);
  struct Node *parent1 = x->parent;
  if (sibling1 == NULL) {
    // No sibiling, double black pushed up
    Head = FixDoubleBlack(Head, parent1);
  } else {
    if (sibling1->color == RED) {
      // Sibling red
      parent1->color = RED;
      sibling1->color = 0;
      if (sibling1->parent->left == sibling1) {
        // left case
        Head = RightRotate(Head, parent1);
      } else {
        // right case
        Head = LeftRotate(Head, parent1);
      }
      Head = FixDoubleBlack(Head, x);
    } else {
      // Sibling black
      if (HasRedChild(sibling1)) {
        // at least 1 red children
        if (sibling1->left != NULL && sibling1->left->color == RED) {
          if (sibling1->parent->left == sibling1) {
            // left left
            sibling1->left->color = sibling1->color;
            sibling1->color = parent1->color;
            Head = RightRotate(Head, parent1);
          } else {
            // right left
            sibling1->left->color = parent1->color;
            Head = RightRotate(Head, sibling1);
            Head = LeftRotate(Head, parent1);
          }
        } else {
          if (sibling1->parent->left == sibling1) {
            // left right
            sibling1->right->color = parent1->color;
            Head = LeftRotate(Head, sibling1);
            Head = RightRotate(Head, parent1);
          } else {
            // right right
            sibling1->right->color = sibling1->color;
            sibling1->color = parent1->color;
            Head = LeftRotate(Head, parent1);
          }
        }
        parent1->color = 0;
      } else {
        // 2 black children
        sibling1->color = RED;
        if (parent1->color == 0)
          Head = FixDoubleBlack(Head, parent1);
        else
          parent1->color = 0;
      }
    }
  }
  return Head;
}
struct Node *DeleteNode(struct Node *Head, struct Node *v) {
  struct Node *u = RBTreplace(v);

  // True when u and v are both black
  bool uvBlack = ((u == NULL || u->color == 0) && (v->color == 0));
  struct Node *parent1 = v->parent;

  if (u == NULL) {
    // u is NULL therefore v is leaf
    if (v == Head) {
      // v is root, making root null
      Head = NULL;
    } else {
      if (uvBlack) {
        // u and v both black
        // v is leaf, fix double black at v
        Head = FixDoubleBlack(Head, v);
      } else {
        // u or v is red
        if (FindSibling(v) != NULL)
          // sibling is not null, make it red"
          FindSibling(v)->color = RED;
      }

      // delete v from the tree
      if (v->parent->left == v) {
        parent1->left = NULL;
      } else {
        parent1->right = NULL;
      }
    }
    free(v);
    return Head;
  }

  if (v->left == NULL || v->right == NULL) {
    // v has 1 child
    if (v == Head) {
      // v is root, assign the value of u to v, and delete u
      v->UserID = u->UserID;
      v->left = v->right = NULL;
      free(u);
    } else {
      // Detach v from tree and move u up
      if (v->parent->left == v) {
        parent1->left = u;
      } else {
        parent1->right = u;
      }
      free(v);
      u->parent = parent1;
      if (uvBlack) {
        // u and v both black, fix double black at u
        Head = FixDoubleBlack(Head, u);
      } else {
        // u or v red, color u black
        u->color = 0;
      }
    }
    return Head;
  }

  // v has 2 children, swap values with successor and recurse
  SwapValues(u, v);
  Head = DeleteNode(Head, u);
  return Head;
}
struct Node *Search(struct Node *Head, int n) {
  struct Node *temp = Head;
  while (temp != NULL) {
    if (n < temp->UserID) {
      if (temp->left == NULL)
        break;
      else
        temp = temp->left;
    } else if (n == temp->UserID) {
      break;
    } else {
      if (temp->right == NULL)
        break;
      else
        temp = temp->right;
    }
  }

  return temp;
}
struct Node *Insert(struct Node *Head, int n) {
  //struct Node *newNode = new Node(n);
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->right = NULL;
  newNode->left = NULL;
  newNode->parent = NULL;
  newNode->UserID = n;
  newNode->color = 1;

  if (Head == NULL) {
    // when root is null
    // simply insert value at root
    newNode->color = 0;
    Head = newNode;
  } else {
    struct Node *temp = Search(Head, n);

    if (temp->UserID == n) {
      printf("BOTH Already FRIENDS\n\n");
      return Head;
    }

    // if value is not found, search returns the node
    // where the value is to be inserted

    // connect new node to correct node
    //if (temp == Head)
    //    printf("head is the only node");

    newNode->parent = temp;

    if (n < temp->UserID)
      temp->left = newNode;
    else
      temp->right = newNode;

    // fix red red voilaton if exists
    //Head = fixRedRed(Head, newNode);
    Head = Restructure(Head, newNode);
  }

  return Head;
}
struct Node *DeleteByVal(struct Node *Head, int n) {
  if (Head == NULL)
    // Tree is empty
    return Head;

  struct Node *v = Search(Head, n), *u;

  if (v->UserID != n) {
    //cout << "No node found to delete with value:" << n << endl;
    return Head;
  }
  //if (Head == v)
  //    printf("this is ROOT");
  Head = DeleteNode(Head, v);
  return Head;
}
void DeleteRBTUser(int Value, struct Node *NodeToBeDeleted) {
  if (NodeToBeDeleted == NULL)
    return;
  else {
    DeleteRBTUser(Value, NodeToBeDeleted->left);
    vertex[NodeToBeDeleted->UserID].RootUser = DeleteByVal(vertex[NodeToBeDeleted->UserID].RootUser, Value);
    DeleteRBTUser(Value, NodeToBeDeleted->right);

    free(NodeToBeDeleted);
  }
}
void DeleteRBT_Reverse_User(int Value, struct Node *NodeToBeDeleted) {
  if (NodeToBeDeleted == NULL)
    return;
  else {
    DeleteRBT_Reverse_User(Value, NodeToBeDeleted->left);
    reversevertex[NodeToBeDeleted->UserID].RootUser = DeleteByVal(reversevertex[NodeToBeDeleted->UserID].RootUser, Value);
    DeleteRBT_Reverse_User(Value, NodeToBeDeleted->right);
    free(NodeToBeDeleted);
  }
}

void addUSER(struct User userTObeInserted) {
  userTObeInserted.RootUser = NULL;
  vertex[userTObeInserted.uid] = userTObeInserted;

  userTObeInserted.RootUser = NULL;
  reversevertex[userTObeInserted.uid] = userTObeInserted;

  exist[userTObeInserted.uid] = true;
}
void DeleteUSER(int nodetobedeleted) {

  //if (exist[nodetobedeleted] == false)
  //    printf("User doesn't exist");

  DeleteRBTUser(nodetobedeleted, reversevertex[nodetobedeleted].RootUser);
  DeleteRBT_Reverse_User(nodetobedeleted, vertex[nodetobedeleted].RootUser);
  reversevertex[nodetobedeleted].RootUser = NULL;
  vertex[nodetobedeleted].RootUser = NULL;

  exist[nodetobedeleted] = false;
}
void addfriends(int UserIdOfUser, int UserIdOfFriend) {
  if ((exist[UserIdOfUser] == false) || (exist[UserIdOfFriend] == false)) {
    printf("Atleast one of the user dont exist");
    return;
  }

  vertex[UserIdOfUser].RootUser = Insert(vertex[UserIdOfUser].RootUser, UserIdOfFriend);
  reversevertex[UserIdOfFriend].RootUser = Insert(reversevertex[UserIdOfFriend].RootUser, UserIdOfUser);
}
void Deletefriends(int UserIdOfUser, int UserIdOfFriend) {
  if ((exist[UserIdOfUser] == false) || (exist[UserIdOfFriend] == false)) {
    printf("Atleast one of the user dont exist");
    return;
  }
  vertex[UserIdOfUser].RootUser = DeleteByVal(vertex[UserIdOfUser].RootUser, UserIdOfFriend);
  reversevertex[UserIdOfFriend].RootUser = DeleteByVal(reversevertex[UserIdOfFriend].RootUser, UserIdOfUser);
}
int Findfrienshipstatus(int User1, int User2) {
  if ((exist[User1] == false) || (exist[User2] == false)) {
    //printf("One of the users dont exist\n");
    return 0;
  }

  struct Node *temp = Search(vertex[User1].RootUser, User2);
  if (temp->UserID == User2) {
    //printf("%d is friend of %d", User2, User1);
    return 1;
  } else {
    //printf("%d is not friend of %d", User2, User1);
    return 0;
  }
}

int compatibilityScore(struct User u1, struct User u2) {
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

int NoRecUsers = 0;
int CurIndex = 1;
int FinIndex = 1;

int visitedForRecommendation[1000000];
int FriendofUser[1000000];
int Queueforbfs[1000000];
int LevelForQueueforbfs[1000000];

struct FriendQuality {
  int userid;
  int similarityscore;
  int level;
};
struct FriendQuality Recommendation[1000000];
struct FriendQuality temp1[2000005];
struct FriendQuality temp2[2000005];
struct FriendQuality NullFriendQuality = {0, 0, 0};

void merge(int left, int mid, int right) {

  int size1 = mid - left + 1;
  int size2 = right - mid;

  for (int i = 0; i < size1; i++)
    temp1[i] = Recommendation[left + i];
  for (int i = 0; i < size2; i++)
    temp2[i] = Recommendation[mid + 1 + i];
  int i = 0;
  int j = 0;
  int pos = left;

  while ((i < size1) && (j < size2)) {
    if (temp1[i].level < temp2[j].level) {
      Recommendation[pos] = temp1[i];
      i++;
    } else if (temp1[i].level > temp2[j].level) {
      Recommendation[pos] = temp2[j];
      j++;
    } else {
      if (temp1[i].similarityscore > temp2[j].similarityscore) {
        Recommendation[pos] = temp1[i];
        i++;
      } else if (temp1[i].similarityscore < temp2[j].similarityscore) {
        Recommendation[pos] = temp2[j];
        j++;
      } else {
        if (temp1[i].userid <= temp2[j].userid) {
          Recommendation[pos] = temp1[i];
          i++;
        } else if (temp1[i].userid > temp2[j].userid) {
          Recommendation[pos] = temp2[j];
          j++;
        }
      }
    }
    pos++;
  }
  while (i < size1) {
    Recommendation[pos] = temp1[i];
    i++;
    pos++;
  }

  while (j < size2) {
    Recommendation[pos] = temp2[j];
    j++;
    pos++;
  }
}
void mergeSort(int left, int right) {
  if (left < right) {
    int mid = left + ((right - left) / 2);

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    merge(left, mid, right);
  }
}
//add friends to FriendsofUser
void IniFriendOfUser(struct Node *trav, int x) {
  if (trav == NULL)
    return;
  IniFriendOfUser(trav->left, x);
  FriendofUser[trav->UserID] = x;
  IniFriendOfUser(trav->right, x);
}
void clearQueue(int j) {
  for (int i = 0; i <= j; i++) {
    visitedForRecommendation[Queueforbfs[i]] = 0;
    Queueforbfs[i] = 0;
    LevelForQueueforbfs[i] = 0;
  }
}
void clearRecomd(int j) {
  for (int i = 0; i <= j; i++) {
    Recommendation[i] = NullFriendQuality;
    temp1[i] = NullFriendQuality;
    temp2[i] = NullFriendQuality;
  }
}
//addtoQueueToBFS
void TraverseBFSNODE(struct Node *trav, int level) {
  if (trav == NULL)
    return;
  TraverseBFSNODE(trav->left, level);
  //printf("inside traverse %d\n", trav->UserID);

  if (visitedForRecommendation[trav->UserID] == 0) {
    Queueforbfs[FinIndex + 1] = trav->UserID;
    LevelForQueueforbfs[FinIndex + 1] = level + 1;

    FinIndex++;
    //printf("inside traverse %d,finindex %d\n", trav->UserID, FinIndex);

    if (FriendofUser[trav->UserID] == 0) {
      struct FriendQuality temp;

      temp.userid = trav->UserID;
      temp.level = level + 1;
      temp.similarityscore = 0;

      Recommendation[NoRecUsers + 1] = temp;

      NoRecUsers++;
    }
    //visitedForRecommendation[trav->UserID] = 1;
  }
  TraverseBFSNODE(trav->right, level);
}
void Recommendfriends(int Userid, int K, int maximumUserID) {
  struct Node *Root = (struct Node *)malloc(sizeof(struct Node));
  Root = vertex[Userid].RootUser;

  IniFriendOfUser(Root, 1);

  Queueforbfs[1] = Userid;
  LevelForQueueforbfs[1] = 0;
  //visitedForRecommendation[Userid] = 1;
  NoRecUsers = 0;
  while (CurIndex <= FinIndex) {
    if (visitedForRecommendation[Queueforbfs[CurIndex]] == 1) {
      CurIndex++;
    } else {
      TraverseBFSNODE(vertex[Queueforbfs[CurIndex]].RootUser, LevelForQueueforbfs[CurIndex]);
      visitedForRecommendation[Queueforbfs[CurIndex]] = 1;
      CurIndex++;
    }
    if (K <= NoRecUsers) {
      break;
    }
  }
  if (NoRecUsers < K) {
    for (int i = 1; i <= maximumUserID; i++) {
      if ((exist[i] == 1) && (visitedForRecommendation[i] == 0) && (FriendofUser[i] == 0)) {
        struct FriendQuality temp;
        temp.userid = i;
        temp.level = INT_MAX;
        temp.similarityscore = 0;
        Recommendation[NoRecUsers + 1] = temp;
        NoRecUsers++;
      }
      if (NoRecUsers > K)
        break;
    }
  }
  for (int i = 1; i <= NoRecUsers; i++) {
    Recommendation[i].similarityscore = compatibilityScore(vertex[Recommendation[i].userid], vertex[Userid]);
  }
  mergeSort(1, NoRecUsers);
  int NoRecUsersFinal = NoRecUsers;
  if (K < NoRecUsers)
    NoRecUsersFinal = K;
  printf("\nNO OF RECOMMENDED USERS IS: %d\n", NoRecUsersFinal);
  for (int i = 1; i <= NoRecUsersFinal; i++) {
    printUser(vertex[Recommendation[i].userid]);
  }
  printf("\n");
  IniFriendOfUser(Root, 0);
  clearQueue(FinIndex);
  clearRecomd(NoRecUsers);
  K = 0;
  CurIndex = 1;
  FinIndex = 1;
  NoRecUsers = 0;
}

int V = 1000000;
struct Heap *h;
void initialize() {
  h = createHeap(V);
}
void addUser() {
  struct User u;
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
  addUSER(u);
  printUser(vertex[u.uid]);
  Recommendfriends(u.uid, 10, minUID - 1);
  if (minUID > 2) {
    int no_of_friends = 0;
    printf("\n\n");
    printf("Enter No of Friends to add:");
    scanf("%d", &no_of_friends);
    printf("\n\n");
    for (int i = 1; i <= no_of_friends; i++) {
      printf("\nEnter 0 to to end adding friends.\n");
      printf("\nEnter the UserID of friend to add.\n\n");
      int frid;

      scanf("%d", &frid);
      if (frid == 0)
        break;
      if (u.uid == frid) {
        printf("\nCannot add user as user's Friend\n");
      } else {
        printUser(vertex[u.uid]);
        printUser(vertex[frid]);
        addfriends(u.uid, frid);
        printf("Added %s as %s\'s Friend.\n",
               vertex[frid].name, vertex[u.uid].name);
      }
    }
  }
}
void searchUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (exist[userid])
    printUser(vertex[userid]);
  else
    printf("EROR 404: USER ID #%d NOT FOUND!\n", userid);

  printf("\n");
}
void searchUserName() {
  system("clear");

  bool found = 0;

  string username;
  printf("Enter the Name: ");
  gets(username);

  for (int i = 1; i < minUID; ++i) {
    if (exist[i] == 1) {
      if (!strcmp(vertex[i].name, username)) {
        printUser(vertex[i]);
        found = 1;
        break;
      }
    }
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

  if (exist[userid]) {
    printUser(vertex[userid]);
    printf("\n");

    printf("Enter the new details\n");
    printf("Name: ");
    gets(vertex[userid].name);
    printf("Age: ");
    gets(vertex[userid].age);
    printf("Gender: ");
    gets(vertex[userid].gender);
    printf("Email: ");
    gets(vertex[userid].email);
    printf("Job Title: ");
    gets(vertex[userid].job_title);
    printf("University: ");
    gets(vertex[userid].university);
    printf("City: ");
    gets(vertex[userid].city);
    printf("Country: ");
    gets(vertex[userid].country);

    printf("Edited.\n");
    printUser(vertex[userid]);
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

  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, username)) {
        printUser(vertex[i]);
        printf("\n");

        printf("Enter the new details\n");
        printf("Name: ");
        gets(vertex[i].name);
        printf("Age: ");
        gets(vertex[i].age);
        printf("Gender: ");
        gets(vertex[i].gender);
        printf("Email: ");
        gets(vertex[i].email);
        printf("Job Title: ");
        gets(vertex[i].job_title);
        printf("University: ");
        gets(vertex[i].university);
        printf("City: ");
        gets(vertex[i].city);
        printf("Country: ");
        gets(vertex[i].country);

        printf("Edited.\n");
        printUser(vertex[i]);
        found = 1;
        break;
      }
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

  for (int i = 1; i < minUID; ++i)
    if (exist[i]) {
      if (!found)
        found = 1;
      printUser(vertex[i]);
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
void removeUserUID() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (exist[userid]) {
    printUser(vertex[userid]);
    printf("Confirm Delete (y/n)? ");
    char c, buff;
    scanf("%c%c", &buff, &c);
    if (c != 'n') {
      printf("Deleted!\n");
      DeleteUSER(userid);
      insertHeap(h, userid);
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

  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, username)) {
        printUser(vertex[i]);
        printf("Confirm Delete (y/n)? ");
        char c, buff;
        scanf("%c%c", &buff, &c);

        if (c != 'n') {
          printf("Deleted!\n");
          DeleteUSER(vertex[i].uid);
          insertHeap(h, i);
          found = 1;
        } else {
          printf("Skipped!\n");
        }
        break;
      }
    }
  if (!found)
    printf("ERROR 404: USER \"%s\" NOT FOUND.", username);

  printf("\n");
}
void addFriendshipUID() {
  system("clear");

  int userid, friendid;
  printf("Enter the User ID and the Friend ID: ");
  scanf("%d %d", &userid, &friendid);

  if (exist[userid] && exist[friendid]) {
    if (userid == friendid) {
      printf("Cannot add user as user's Friend\n");
    } else {
      printUser(vertex[userid]);
      printUser(vertex[friendid]);
      addfriends(userid, friendid);
      printf("Added %s as %s\'s Friend.\n",
             vertex[friendid].name, vertex[userid].name);
    }
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

  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, username)) {
        userid = i;
        founduser = 1;
        printUser(vertex[i]);
        break;
      }
    }

  if (!founduser) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);
  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, friendname)) {
        friendid = i;
        foundfriend = 1;
        printUser(vertex[i]);
        break;
      }
    }

  if (!foundfriend) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }
  if (userid == friendid) {
    printf("Cannot add user as user's Friend\n");
  } else {
    addfriends(userid, friendid);
    printf("Added %s as %s\'s Friend.\n",
           vertex[friendid].name, vertex[userid].name);
  }
  printf("\n");
}
void recommendFriendsExistingUser() {
  system("clear");

  int userid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (exist[userid] == 0) {
    printf("ERROR 404: USER #%d NOT FOUND.\n", userid);
    return;
  }

  printf("------> ");
  printUser(vertex[userid]);

  int toAdd;
  printf("Enter the number of friends you want to add: ");
  scanf("%d", &toAdd);

  if (toAdd == 0) {
    printf("Skipping Recommending Friends...\n");
    recommendFriendsMenu();
  }

  int no_of_friends = 0;
  Recommendfriends(userid, toAdd, minUID - 1);
  printf("\n\n");
  printf("Enter No of Friends to add:");
  scanf("%d", &no_of_friends);
  printf("\n\n");
  for (int i = 1; i <= no_of_friends; i++) {
    printf("\nEnter 0 to to end adding friends.\n");
    printf("\nEnter the UserID of friend to add.\n\n");
    int frid;

    scanf("%d", &frid);
    if (frid == 0)
      break;
    if (userid == frid) {
      printf("\nCannot add user as user's Friend\n");
    } else {
      printUser(vertex[userid]);
      printUser(vertex[frid]);
      addfriends(userid, frid);
      printf("Added %s as %s\'s Friend.\n",
             vertex[frid].name, vertex[userid].name);
    }
  }
}
void checkFriendshipUID() {
  system("clear");

  int userid, friendid;
  printf("Enter the User ID: ");
  scanf("%d", &userid);

  if (exist[userid] == 0) {
    printf("ERROR 404: USER #%03d NOT FOUND!\n", userid);
    return;
  }

  printf("Enter the Friend ID: ");
  scanf("%d", &friendid);

  if (exist[friendid] == 0) {
    printf("ERROR 404: USER #%03d NOT FOUND!\n", friendid);
    return;
  }
  bool friend12 = Findfrienshipstatus(userid, friendid);
  bool friend21 = Findfrienshipstatus(friendid, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", vertex[userid].name,
           vertex[friendid].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", vertex[userid].name,
           vertex[friendid].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", vertex[friendid].name,
           vertex[userid].name);
  else
    printf("%s and %s are not Friends.\n", vertex[userid].name,
           vertex[friendid].name);

  printf("\n");
}
void checkFriendshipName() {
  system("clear");

  bool founduser = 0, foundfriend = 0;
  int userid = 0, friendid = 0;
  string username, friendname;

  printf("Enter the User Name: ");
  gets(username);

  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, username)) {
        userid = i;
        founduser = 1;
        printUser(vertex[i]);
        break;
      }
    }

  if (!founduser) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", username);
    return;
  }

  printf("Enter the Friend's Name: ");
  gets(friendname);

  for (int i = 0; i < minUID; ++i)
    if (exist[i]) {
      if (!strcmp(vertex[i].name, friendname)) {
        friendid = i;
        foundfriend = 1;
        printUser(vertex[i]);
        break;
      }
    }

  if (!foundfriend) {
    printf("ERROR 404: USER \"%s\" NOT FOUND.\n", friendname);
    return;
  }

  bool friend12 = Findfrienshipstatus(userid, friendid);
  bool friend21 = Findfrienshipstatus(friendid, userid);

  if (friend12 && friend21)
    printf("%s and %s are Mutual Friends.\n", vertex[userid].name,
           vertex[friendid].name);
  else if (friend12)
    printf("%s considers %s to be a friend.\n", vertex[userid].name,
           vertex[friendid].name);
  else if (friend21)
    printf("%s considers %s to be a friend.\n", vertex[friendid].name,
           vertex[userid].name);
  else
    printf("%s and %s are not Friends.\n", vertex[userid].name,
           vertex[friendid].name);

  printf("\n");
}
void printFriendlist(struct Node *root) {
  if (root != NULL) {
    printFriendlist(root->left);
    printf("%s | ", vertex[root->UserID].name);
    printFriendlist(root->right);
  }
}
// Displays the Frienship Network
void displayFriendsAdjacencyList() {
  system("clear");

  bool found = 0;

  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------");
  printf("-------------------------------------------------------\n");

  for (int i = 1; i < minUID; ++i) {
    if (exist[i]) {
      if (!found)
        found = 1;

      printf("Friends of [%03d] %25s: ", vertex[i].uid, vertex[i].name);

      if (vertex[i].RootUser)
        printFriendlist(vertex[i].RootUser);
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

void banner();
void authorization();
void mainMenu();
void userMenu();
void friendMenu();
void addFriendMenu();
void checkFriendMenu();
void ViewFriendShipNetwork();
void recommendFriendsMenu();
void searchUserMenu();
void editUserMenu();
void removeUserMenu();
void displayFriendsMenu();
void quit();
void importData();
void banner() {
  system("clear");

  printf("  **************************************  \n");
  printf("  **************************************  \n");
  printf("  **                                  **  \n");
  printf("  **              Amigos              **  \n");
  printf("  **                                  **  \n");
  printf("  **************************************  \n");
  printf("  **************************************  \n");
  printf("\n");
}
void mainMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **            Main Menu             **  \n");
    printf("  **                                  **  \n");
    printf("  **       1. User Management         **  \n");
    printf("  **       2. Friend Management       **  \n");
    printf("  **                                  **  \n");
    printf("  **         0. Exit Amigos           **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      userMenu();
      break;
    case 2:
      friendMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      mainMenu();
    }
  } while (ch <= 100);
}
void userMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **          User Management         **  \n");
    printf("  **                                  **  \n");
    printf("  **        1. Register User          **  \n");
    printf("  **        2. Search User            **  \n");
    printf("  **        3. Edit User              **  \n");
    printf("  **        4. Display User           **  \n");
    printf("  **        5. Unregister User        **  \n");
    printf("  **                                  **  \n");
    printf("  **     9. Back to the Main Menu     **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      addUser();
      break;
    case 2:
      searchUserMenu();
      break;
    case 3:
      editUserMenu();
      break;
    case 4:
      displayUserDatabase();
      break;
    case 5:
      removeUserMenu();
      break;
    case 7:
      //importData();
      break;
    case 9:
      mainMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      userMenu();
    }
  } while (ch <= 100);
}
void searchUserMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **          User Management         **  \n");
    printf("  **                                  **  \n");
    printf("  **            Search User           **  \n");
    printf("  **                                  **  \n");
    printf("  **      1. Search User by UID       **  \n");
    printf("  **      2. Search User by Name      **  \n");
    printf("  **                                  **  \n");
    printf("  **     9. Back to the User Menu     **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      searchUserUID();
      break;
    case 2:
      searchUserName();
      break;
    case 9:
      userMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      searchUserMenu();
    }
  } while (ch <= 100);
}
void editUserMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **          User Management         **  \n");
    printf("  **                                  **  \n");
    printf("  **            Edit User             **  \n");
    printf("  **                                  **  \n");
    printf("  **       1. Edit User by UID        **  \n");
    printf("  **       2. Edit User by Name       **  \n");
    printf("  **                                  **  \n");
    printf("  **     9. Back to the User Menu     **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      editUserUID();
      break;
    case 2:
      editUserName();
      break;
    case 9:
      userMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      editUserMenu();
    }
  } while (ch <= 100);
}
void removeUserMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **          User Management         **  \n");
    printf("  **                                  **  \n");
    printf("  **            Remove User           **  \n");
    printf("  **                                  **  \n");
    printf("  **      1. Remove User by UID       **  \n");
    printf("  **      2. Remove User by Name      **  \n");
    printf("  **                                  **  \n");
    printf("  **                                  **  \n");
    printf("  **     9. Back to the User Menu     **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      removeUserUID();
      break;
    case 2:
      removeUserName();
      break;
    case 9:
      userMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      searchUserMenu();
    }
  } while (ch <= 100);
}
void friendMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **         Friend Management        **  \n");
    printf("  **                                  **  \n");
    printf("  **      1. Add Friendship           **  \n");
    printf("  **      2. Recommend Friends        **  \n");
    printf("  **      3. Check Friendship         **  \n");
    printf("  **      4. Display Friendships      **  \n");
    //printf("  **      5. Delete Friends           **  \n");
    printf("  **                                  **  \n");
    printf("  **     9. Back to the Main Menu     **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      addFriendMenu();
      break;
    case 2:
      recommendFriendsMenu();
      break;
    case 3:
      checkFriendMenu();
      break;
    case 4:
      displayFriendsMenu();
      break;
    case 9:
      mainMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      friendMenu();
    }
  } while (ch <= 100);
}
void addFriendMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **         Friend Management        **  \n");
    printf("  **                                  **  \n");
    printf("  **          Add Friendship          **  \n");
    printf("  **                                  **  \n");
    printf("  **    1. Add Friendship by UIDs     **  \n");
    printf("  **    2. Add Friendship by Names    **  \n");
    printf("  **                                  **  \n");
    printf("  **    9. Back to the Friend Menu    **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      addFriendshipUID();
      break;
    case 2:
      addFriendshipName();
      break;
    case 9:
      friendMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      friendMenu();
    }
  } while (ch <= 100);
}
void recommendFriendsMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **         Friend Management        **  \n");
    printf("  **                                  **  \n");
    printf("  **         Recommend Friends        **  \n");
    printf("  **                                  **  \n");
    //printf("  **      1. To a New User            **  \n");
    printf("  **      1. To a User          	    **  \n");
    printf("  **                                  **  \n");
    printf("  **    9. Back to the Friend Menu    **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      recommendFriendsExistingUser();
      break;
    case 9:
      friendMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      friendMenu();
    }
  } while (ch <= 100);
}
void checkFriendMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **         Friend Management        **  \n");
    printf("  **                                  **  \n");
    printf("  **         Check Friendship         **  \n");
    printf("  **                                  **  \n");
    printf("  **    1. Check Friendship by UID    **  \n");
    printf("  **    2. Check Friendship by Name   **  \n");
    printf("  **                                  **  \n");
    printf("  **    9. Back to the Friend Menu    **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      checkFriendshipUID();
      break;
    case 2:
      checkFriendshipName();
      break;
    case 9:
      friendMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      friendMenu();
    }
  } while (ch <= 100);
}
void displayFriendsMenu() {
  system("clear");

  int ch;
  do {
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **         Friend Management        **  \n");
    printf("  **                                  **  \n");
    printf("  **        Display Friendships       **  \n");
    printf("  **                                  **  \n");
    printf("  **    1. Display Adjacency List     **  \n");
    printf("  **                                  **  \n");
    printf("  **                                  **  \n");
    printf("  **    9. Back to the Friend Menu    **  \n");
    printf("  **          0. Exit Amigos          **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("\n");

    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      displayFriendsAdjacencyList();
      break;
    case 9:
      friendMenu();
      break;
    case 0:
      quit();
    default:
      printf("Invalid Choice!\n");
      friendMenu();
    }
  } while (ch <= 100);
}

void quit() {
  system("clear");
  printf("Thank You for visiting us at https://amigos.com/\n");
  exit(0);
}

int main() {
  banner();
  // authorization();
  initialize();
  mainMenu();
}
