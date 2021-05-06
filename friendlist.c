/** C implementation for
	Red-Black Tree Insertion
	This code is provided by
	costheta_z **/
#include <stdio.h>
#include <stdlib.h>






// Structure to represent each
// node in a red-black tree
struct node {
	int data; // data
	int color; // 1-red, 0-black
	struct node* parent; // parent
	struct node* right; // right-child
	struct node* left; // left child
};

struct vertex {
    struct node* root1;
    

};

struct vertex a[10000000];

//function to insert node
struct node* RedBlackTree(struct node* head,struct node* temp)
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
struct node* root = NULL;
/*
// function to perform BST insertion of a node
struct node* bst(struct node* trav,struct node* temp)
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
struct node* rightrotate(struct node* head ,struct node* temp)
{
	struct node* left = temp->left;
	
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

struct node* leftrotate(struct node* head ,struct node* temp)
{
	struct node* right = temp->right;

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

struct node* restructure(struct node* head, struct node* pt)
{
	struct node* parent_pt = NULL;
	struct node* grand_parent_pt = NULL;

	while ((pt != head) && (pt->color != 0) && (pt->parent->color == 1))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of pt 
		*/
		if (parent_pt == grand_parent_pt->left)
		{

			struct node* uncle_pt = grand_parent_pt->right;

			/* Case : 1
				The uncle of pt is also red
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

				/* Case : 2
					pt is right child of its parent
					Left-rotation required 
				*/
				if (pt == parent_pt->right) 
				{
					head = leftrotate(head,parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
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

		/* Case : B
			Parent of pt is right child of Grand-parent of pt 
		*/
		else 
		{
			struct node* uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of pt is also red
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
				/* Case : 2
					pt is left child of its parent
					Right-rotation required 
				*/
				
				if (pt == parent_pt->left) 
				{
					head = rightrotate(head,parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/* Case : 3
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









/*
// Function to print inorder traversal
// of the fixated tree
void inorder(struct node* trav)
{
	if (trav == NULL)
		return;
	inorder(trav->l);
	printf("%d ", trav->d);
	inorder(trav->r);
}
/*
// driver code
int main()
{
	int n = 7;
	int a[7] = { 7, 6, 5, 4, 3, 2, 1 };

	for (int i = 0; i < n; i++) {

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array
		struct node* temp
			= (struct node*)malloc(sizeof(struct node));
		temp->r = NULL;
		temp->l = NULL;
		temp->parent = NULL;
		temp->d = a[i];
		temp->c = 1;

		// calling function that performs bst insertion of
		// this newly created node
		root = bst(root, temp);

		// calling function to preserve properties of rb
		// tree
		fixup(root, temp);
	}

	printf("Inoder Traversal of Created Tree\n");
	inorder(root);

	return 0;
}
*/