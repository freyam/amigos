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
treeNode *newNode(int friend_id) {
  treeNode *node = (treeNode *)malloc(sizeof(treeNode));
  node->friend_id = friend_id;
  node->left_child = NULL;
  node->right_child = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
treeNode *rightRotate(treeNode *y) {
  treeNode *x = y->left_child;
  treeNode *T2 = x->right_child;

  x->right_child = y;
  y->left_child = T2;

  y->height = max(height(y->left_child), height(y->right_child)) + 1;
  x->height = max(height(x->left_child), height(x->right_child)) + 1;

  return x;
}

// Left rotate
treeNode *leftRotate(treeNode *x) {
  treeNode *y = x->right_child;
  treeNode *T2 = y->left_child;

  y->left_child = x;
  x->right_child = T2;

  x->height = max(height(x->left_child), height(x->right_child)) + 1;
  y->height = max(height(y->left_child), height(y->right_child)) + 1;

  return y;
}

// Get the balance factor
int getBalance(treeNode *N) {
  if (N == NULL)
    return 0;
  return height(N->left_child) - height(N->right_child);
}

// Insert node
treeNode *insertTreeNode(treeNode *node, int friend_id) {
  // Find the correct position to insertTreeNode the node and insertTreeNode it
  if (node == NULL)
    return (newNode(friend_id));

  if (friend_id < node->friend_id)
    node->left_child = insertTreeNode(node->left_child, friend_id);
  else if (friend_id > node->friend_id)
    node->right_child = insertTreeNode(node->right_child, friend_id);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left_child), height(node->right_child));

  int balance = getBalance(node);
  if (balance > 1 && friend_id < node->left_child->friend_id)
    return rightRotate(node);

  if (balance < -1 && friend_id > node->right_child->friend_id)
    return leftRotate(node);

  if (balance > 1 && friend_id > node->left_child->friend_id) {
    node->left_child = leftRotate(node->left_child);
    return rightRotate(node);
  }

  if (balance < -1 && friend_id < node->right_child->friend_id) {
    node->right_child = rightRotate(node->right_child);
    return leftRotate(node);
  }

  return node;
}

treeNode *minValueNode(treeNode *node) {
  treeNode *current = node;

  while (current->left_child != NULL)
    current = current->left_child;

  return current;
}

// Delete a nodes
treeNode *deleteNode(treeNode *root, int friend_id) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (friend_id < root->friend_id)
    root->left_child = deleteNode(root->left_child, friend_id);

  else if (friend_id > root->friend_id)
    root->right_child = deleteNode(root->right_child, friend_id);

  else {
    if ((root->left_child == NULL) || (root->right_child == NULL)) {
      treeNode *temp = root->left_child ? root->left_child : root->right_child;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      treeNode *temp = minValueNode(root->right_child);

      root->friend_id = temp->friend_id;

      root->right_child = deleteNode(root->right_child, temp->friend_id);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left_child),
                         height(root->right_child));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left_child) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left_child) < 0) {
    root->left_child = leftRotate(root->left_child);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right_child) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right_child) > 0) {
    root->right_child = rightRotate(root->right_child);
    return leftRotate(root);
  }

  return root;
}

// Print the trees
void printPreOrder(treeNode *root) {
  if (root != NULL) {
    printPreOrder(root->left_child);
    printf("%d ", root->friend_id);
    printPreOrder(root->right_child);
  }
}

bool findFriend(treeNode *root, int fid) {
  if (root == NULL)
    return 0;

  if (root->friend_id == fid)
    return 1;

  int leftcheck = findFriend(root->left_child, fid);
  if (leftcheck)
    return 1;

  return findFriend(root->right_child, fid);
}

void singlePass(treeNode *root, Queue *q, bool visited[]) {
  if (root != NULL) {
    singlePass(root->left_child, q, visited);
    visited[root->friend_id] = 1;
    enqueue(q, root->friend_id);
    // printf("%d ", root->friend_id);
    singlePass(root->right_child, q, visited);
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