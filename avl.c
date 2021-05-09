#include "amigos.h"

// Calculate height
int height(treeNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node
treeNode *newNode(int friendid) {
  treeNode *node = (treeNode *)malloc(sizeof(treeNode));
  node->friendid = friendid;
  node->leftchild = NULL;
  node->rightchild = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
treeNode *rightRotate(treeNode *y) {
  treeNode *x = y->leftchild;
  treeNode *T2 = x->rightchild;

  x->rightchild = y;
  y->leftchild = T2;

  y->height = max(height(y->leftchild), height(y->rightchild)) + 1;
  x->height = max(height(x->leftchild), height(x->rightchild)) + 1;

  return x;
}

// Left rotate
treeNode *leftRotate(treeNode *x) {
  treeNode *y = x->rightchild;
  treeNode *T2 = y->leftchild;

  y->leftchild = x;
  x->rightchild = T2;

  x->height = max(height(x->leftchild), height(x->rightchild)) + 1;
  y->height = max(height(y->leftchild), height(y->rightchild)) + 1;

  return y;
}

// Get the balance factor
int getBalance(treeNode *N) {
  if (N == NULL)
    return 0;
  return height(N->leftchild) - height(N->rightchild);
}

// Insert node
treeNode *insertTreeNode(treeNode *node, int friendid) {
  // Find the correct position to insertTreeNode the node and insertTreeNode it
  if (node == NULL)
    return (newNode(friendid));

  if (friendid < node->friendid)
    node->leftchild = insertTreeNode(node->leftchild, friendid);
  else if (friendid > node->friendid)
    node->rightchild = insertTreeNode(node->rightchild, friendid);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->leftchild), height(node->rightchild));

  int balance = getBalance(node);
  if (balance > 1 && friendid < node->leftchild->friendid)
    return rightRotate(node);

  if (balance < -1 && friendid > node->rightchild->friendid)
    return leftRotate(node);

  if (balance > 1 && friendid > node->leftchild->friendid) {
    node->leftchild = leftRotate(node->leftchild);
    return rightRotate(node);
  }

  if (balance < -1 && friendid < node->rightchild->friendid) {
    node->rightchild = rightRotate(node->rightchild);
    return leftRotate(node);
  }

  return node;
}

treeNode *minValueNode(treeNode *node) {
  treeNode *current = node;

  while (current->leftchild != NULL)
    current = current->leftchild;

  return current;
}

// Delete a nodes
treeNode *deleteNode(treeNode *root, int friendid) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (friendid < root->friendid)
    root->leftchild = deleteNode(root->leftchild, friendid);

  else if (friendid > root->friendid)
    root->rightchild = deleteNode(root->rightchild, friendid);

  else {
    if ((root->leftchild == NULL) || (root->rightchild == NULL)) {
      treeNode *temp = root->leftchild ? root->leftchild : root->rightchild;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      treeNode *temp = minValueNode(root->rightchild);

      root->friendid = temp->friendid;

      root->rightchild = deleteNode(root->rightchild, temp->friendid);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->leftchild),
                         height(root->rightchild));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->leftchild) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->leftchild) < 0) {
    root->leftchild = leftRotate(root->leftchild);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->rightchild) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->rightchild) > 0) {
    root->rightchild = rightRotate(root->rightchild);
    return leftRotate(root);
  }

  return root;
}

// Print the trees
void printPreOrder(treeNode *root) {
  if (root != NULL) {
    printPreOrder(root->leftchild);
    printf("%d ", root->friendid);
    printPreOrder(root->rightchild);
  }
}

bool findFriend(treeNode *root, int fid) {
  if (root == NULL)
    return 0;

  if (root->friendid == fid)
    return 1;

  int leftcheck = findFriend(root->leftchild, fid);
  if (leftcheck)
    return 1;

  return findFriend(root->rightchild, fid);
}

void firstPass(treeNode *root, Queue *q, bool visited[]) {
  if (root != NULL) {
    firstPass(root->leftchild, q, visited);
    visited[root->friendid] = 1;
    enqueue(q, root->friendid);
    // printf("%d ", root->friendid);
    firstPass(root->rightchild, q, visited);
  }
}

// int main() {
//   treeNode *root = NULL;

//   root = insertTreeNode(root, 3);
//   root = insertTreeNode(root, 2);
//   root = insertTreeNode(root, 1);
//   root = insertTreeNode(root, 7);
//   root = insertTreeNode(root, 4);
//   root = insertTreeNode(root, 5);
//   root = insertTreeNode(root, 8);
//   printPreOrder(root);

//   printf("\n3 -> %d", findFriend(root, 3));

//   root = deleteNode(root, 3);

//   printf("\nAfter deletion: ");
//   printPreOrder(root);

//   printf("\n3 -> %d", findFriend(root, 3));

//   return 0;
// }