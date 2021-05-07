/**C implementation for
	Red-Black Tree Insertion
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <amigos.h>


int BLACK=0;
int RED=1;



// Structure to represent each
// node in a RED-BLACK tree
struct node {
	struct User *data; // data
	int color; // 1-RED, 0-BLACK
	struct node *parent; // parent
	struct node *right; // right-child
	struct node *left; // left child
};



//function to insert node
struct node *RedBlackTree(struct node *head,struct node *temp)
{
    //If RBT is empty
    //Return the new node
    if(head == NULL)
    {
        return temp;
    }
    else
    {
        if (temp->data < head->data)
	    {
		    head->left = RedBlackTree(head->left, temp);
		    head->left->parent = head;
	    }
	    else if (temp->data > head->data)
	    {
		    head->right = RedBlackTree(head->right, temp);
		    head->right->parent = head;
	    }

	// Return the (unchanged) node pointer
	return head;
    }

}




// global root for the entire tree
//struct node *root = NULL;
/*
// function to perform BST insertion of a node
struct node *bst(struct node *trav,struct node *temp)
{
	// If the tree is empty,
	// return a new node
	if (trav == NULL)
		return temp;

	// Otherwise recur down the tree
	if (temp->d < trav->d)
	{
		trav->l = bst(trav->l, temp);
		trav->l->p = trav;
	}
	else if (temp->d > trav->d)
	{
		trav->r = bst(trav->r, temp);
		trav->r->p = trav;
	}

	// Return the (unchanged) node pointer
	return trav;
}
*/
// Function performing right rotation
// of the passed node
struct node *rightrotate(struct node *head ,struct node *temp)
{
	struct node *left = temp->left;
	
    temp->left = left->right;
	
    if (temp->left)
    {
		temp->left->parent = temp;
    }


	left->parent = temp->parent;
	
    if (!temp->parent)
    {
		head = left;
    }
	else if (temp == temp->parent->left)
    {
		temp->parent->left = left;
    }
	else
	{
		temp->parent->right = left;
	}

	left->right = temp;
	temp->parent = left;

	return head;
}

// Function performing left rotation
// of the passed node

struct node *leftrotate(struct node *head ,struct node *temp)
{
	struct node *right = temp->right;

	temp->right = right->left;
	
	if (temp->right)
	{
		temp->right->parent = temp;
	}

	right->parent = temp->parent;
	
	if (!temp->parent)
	{
		head = right;
	}
	else if (temp == temp->parent->left)
	{
		temp->parent->left = right;
	}
	else
	{
		temp->parent->right = right;
	}
	right->left = temp;
	temp->parent = right;

	return head;
}

// This function fixes violations
// caused by BST insertion

struct node *restructure(struct node *head, struct node *pt)
{
	struct node *parent_pt = NULL;
	struct node *grand_parent_pt = NULL;

	while ((pt != head) && (pt->color != 0) && (pt->parent->color == 1))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*Case : A
			Parent of pt is left child
			of Grand-parent of pt 
		*/
		if (parent_pt == grand_parent_pt->left)
		{

			struct node *uncle_pt = grand_parent_pt->right;

			/*Case : 1
				The uncle of pt is also RED
				Only Recoloring required 
			*/
			if (uncle_pt != NULL && uncle_pt->color == 1)
			{
				grand_parent_pt->color = 1;
				parent_pt->color = 0;
				uncle_pt->color = 0;
				pt = grand_parent_pt;
			}

			else 
			{

				/*Case : 2
					pt is right child of its parent
					Left-rotation required 
				*/
				if (pt == parent_pt->right) 
				{
					head = leftrotate(head,parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/*Case : 3
					pt is left child of its parent
					Right-rotation required 
				*/
				head = rightrotate(head,grand_parent_pt);
				int t = parent_pt->color;
				parent_pt->color = grand_parent_pt->color;
				grand_parent_pt->color = t;
				pt = parent_pt;
			}
		}

		/*Case : B
			Parent of pt is right child of Grand-parent of pt 
		*/
		else 
		{
			struct node *uncle_pt = grand_parent_pt->left;

			/*Case : 1
				The uncle of pt is also RED
				Only Recoloring required 
			*/
			if ((uncle_pt != NULL) && (uncle_pt->color == 1))
			{
				grand_parent_pt->color = 1;
				parent_pt->color = 0;
				uncle_pt->color = 0;
				pt = grand_parent_pt;
			}
			else 
			{
				/*Case : 2
					pt is left child of its parent
					Right-rotation required 
				*/
				
				if (pt == parent_pt->left) 
				{
					head = rightrotate(head,parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/*Case : 3
					pt is right child of its parent
					Left-rotation required 
				*/
				head = leftrotate(head,grand_parent_pt);

				int t = parent_pt->color;
				parent_pt->color = grand_parent_pt->color;
				grand_parent_pt->color = t;
				pt = parent_pt;

			}
		}
	}

	head->color = 0;

	return head;
}

void swapColors(struct node *x1, struct node *x2) {
	int temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

void swapValues(struct node *u, struct node *v) {
	int temp;
	temp = u->data;
	u->data = v->data;
	v->data = temp;
}


struct node *siblingfind(struct node *x) {
	// sibling null if no parent
	if (x->parent == NULL)
		return NULL;

	if (x->parent->left == x)
		return x->parent->right;

	return x->parent->left;
}

struct node *unclefind(struct node *x) {
	// If no parent or grandparent, then no uncle
	if (x->parent == NULL || x->parent->parent == NULL)
		return NULL;

	if (x->parent->parent->left == x->parent)
		// uncle on right
		return x->parent->parent->right;
	else
		// uncle on left
		return x->parent->parent->left;
}

bool hasRedChild(struct node *x) {
	return (x->left != NULL && x->left->color == RED) ||(x->right != NULL && x->right->color == RED);
}




// fix RED RED at given node
struct node *fixRedRed(struct node *head,struct node *x) 
{
	// if x is root color it BLACK and return
	if (x == head) 
	{
		x->color = 0;//BLACK;
		return head;
	}

	// initialize parent, grandparent, uncle
	struct node *parent = x->parent;
	struct node *grandparent = parent->parent;
	struct node *uncle = unclefind(x);

	if (parent->color != 0) 
	{
		if (uncle != NULL && uncle->color == 1) 
		{
			// uncle RED, perform recoloring and recurse
			parent->color = 0;//BLACK;
			uncle->color = 0;//BLACK;
			grandparent->color = 1;//RED;
			head = fixRedRed(head,grandparent);
		} 
		else 
		{
			// Else perform LR, LL, RL, RR
			if (parent->parent->left == parent) 
			{
				if (x->parent->left == x) 
				{
					// for left right
					swapColors(parent, grandparent);
				}
				else 
				{
					head = leftrotate(head,parent);
					swapColors(x, grandparent);
				}
				// for left left and left right
				head = rightrotate(head,grandparent);
			}
			else 
			{
				if (x->parent->left == x) 
				{
					// for right left
					head = rightrotate(head,parent);
					swapColors(x, grandparent);
				}	 
				else 
				{
					swapColors(parent, grandparent);
				}

				// for right right and right left
				head = leftrotate(head,grandparent);
			}
		}
	}
	return head;
}

// find node that do not have a left child
// in the subtree of the given node
struct node *successor(struct node *x) {
	struct node *temp = x;

	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}

// find node that replaces a deleted node in BST
struct node *BSTreplace(struct node *x) {
	// when node have 2 children
	if (x->left != NULL && x->right != NULL)
		return successor(x->right);

	// when leaf
	if (x->left == NULL && x->right == NULL)
		return NULL;

	// when single child
	if (x->left != NULL)
		return x->left;
	else
		return x->right;
}


struct node *fixDoubleBlack(struct node *head,struct node *x) {
	if (x == head)
	// Reached root
	return head;

	struct node *sibling = siblingfind(x);
	struct node *parent = x->parent;

	if (sibling == NULL) 
	{
		// No sibiling, double BLACK pushed up
		head = fixDoubleBlack(head,parent);
	} 
	else 
	{
		if (sibling->color == RED) 
		{
			// Sibling RED
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling->parent->left == sibling) 
			{
				// left case
				head = rightrotate(head,parent);
			} 
			else 
			{
				// right case
				head = leftrotate(head,parent);
			}
			head = fixDoubleBlack(head,x);
		} 
		else 
		{
			// Sibling BLACK
			if (hasRedChild(sibling)) 
			{
				// at least 1 RED children
				if (sibling->left != NULL && sibling->left->color == RED) 
				{
					if (sibling->parent->left == sibling) 
					{
						// left left
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						head = rightrotate(head,parent);
					} 
					else 
					{
						// right left
						sibling->left->color = parent->color;
						head = rightrotate(head,sibling);
						head = leftrotate(head,parent);
					}
				} 
				else 
				{
					if (sibling->parent->left==sibling) 
					{
						// left right
						sibling->right->color = parent->color;
						head = leftrotate(head,sibling);
						head = rightrotate(head,parent);
					} 
					else 
					{
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						head = leftrotate(head,parent);
					}
				}
				parent->color = BLACK;
			} 
			else 
			{
				// 2 BLACK children
				sibling->color = RED;
				if (parent->color == BLACK)
				{
					head = fixDoubleBlack(head,parent);
				}
				else
				{
					parent->color = BLACK;
				}
			}
		}
	}
	return head;
}


// deletes the given node
struct node *deleteNode(struct node *head ,struct node *v) {
	
	struct node *u = BSTreplace(v);

	// True when u and v are both BLACK
	bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
	struct node *parent = v->parent;

	if (u == NULL) 
	{
		// u is NULL therefore v is leaf
		if (v == head) 
		{
			// v is root, making root null
			head = NULL;
		} 
		else 
		{
			if (uvBlack) 
			{
				// u and v both BLACK
				// v is leaf, fix double BLACK at v
				head = fixDoubleBlack(head,v);
			} 
			else 
			{
				// u or v is RED
				if (siblingfind(v) != NULL)
					// sibling is not null, make it RED"
					siblingfind(v)->color = RED;
			}

			// delete v from the tree
			if (v->parent->left == v) 
			{
				parent->left = NULL;
			} 
			else 
			{
				parent->right = NULL;
			}
		}
		free(v);//delete v;
		return head;
	}

	if (v->left == NULL || v->right == NULL) 
	{
		// v has 1 child
		if (v == head) 
		{
			// v is root, assign the value of u to v, and delete u
			v->data = u->data;
			v->left = v->right = NULL;
			free(u);//delete u;
		} 
		else 
		{
			// Detach v from tree and move u up
			if (v->parent->left == v) 
			{
				parent->left = u;
			} 
			else
			{
				parent->right = u;
			}
			free(v);//delete v;

			u->parent = parent;
			
			if (uvBlack) 
			{
			// u and v both BLACK, fix double BLACK at u
				head = fixDoubleBlack(head,u);
			} 
			else 
			{
				// u or v RED, color u BLACK
				u->color = BLACK;
			}
		}
		return head;
	}

	// v has 2 children, swap values with successor and recurse
	swapValues(u, v);
	head = deleteNode(head,u);

	return head;
}


// searches for given value
// if found returns the node (used for delete)
// else returns the last node while traversing (used in insert)



struct node *search(struct node *head,int n) {
	struct node *temp = head;
	while (temp != NULL) 
	{
		if (n < temp->data) 
		{
			if (temp->left == NULL)
				break;
			else
				temp = temp->left;
		} 
		else if (n == temp->data) 
		{
			break;
		} 
		else 
		{
			if (temp->right == NULL)
				break;
			else
				temp = temp->right;
		}
	}

	return temp;
}

// utility function that deletes the node with given value
struct node *deleteByVal(struct node *head,int n) {
	if (head == NULL)
	// Tree is empty
	return head;

	struct node *v = search(head,n), *u;

	if (v->data != n) 
	{
		printf("No node found to delete with value: %d \n",n);
		//cout << "No node found to delete with value:" << n << '\n';;
		return head;
	}

	head = deleteNode(head,v);

	return head;

}

///*
// Function to print inorder traversal
// of the fixated tree
void inorder(struct node *trav)
{
	if (trav == NULL)
		return;
	inorder(trav->left);
	printf("%d ", trav->data);
	inorder(trav->right);
}
///*
// driver code
int main()
{
	int n = 7;
	int b[7] = { 7, 6, 5, 4, 3, 2, 1 };
	struct node *root;
	
	for (int i = 0; i < n; i++) {

		// allocating memory to the node and initializing:
		// 1. color as RED
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array
		struct node *temp
			= (struct node*)malloc(sizeof(struct node));
		temp->right = NULL;
		temp->left = NULL;
		temp->parent = NULL;
		temp->data = b[i];
		temp->color = 1;

		// calling function that performs bst insertion of
		// this newly created node
		root = RedBlackTree(root, temp);

		// calling function to preserve properties of rb
		// tree
		root = restructure(root, temp);
	}

	printf("Inoder Traversal of Created Tree\n");
	inorder(root);
	printf("\n");
	root = deleteByVal(root,5);
	root = deleteByVal(root,3);
	root = deleteByVal(root,1);

	inorder(root);

	return 0;
}
//*/