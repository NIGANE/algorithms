#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
} Node;

int max(int a, int b) { return a > b ? a : b; }
int getHeight(Node* n){
    if(n == NULL) return 0;
    return n->height;
}

int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* createNode(int data){
    Node* newNode =(Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->height = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}



Node* rightRotate(Node* node){
    Node* x = node->left;
    Node* T2 = x->right;

    x->right = node;
    node->left = T2;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1 ;
    return x;
}
Node* leftRotate(Node* node){
    Node* x = node->right;
    Node* T2 = x->left;

    x->left = node;
    node->right = T2;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node *insertNode(Node *root, int data)
{
    if (root == NULL)
        return createNode(data); // If root is NULL, create a new node.
    else
    {
        
        if (data < root->data)
        {
            root->left = insertNode(root->left, data); // Insert into the left subtree.
        }
        else if (data > root->data)
        {
            root->right = insertNode(root->right, data); // Insert into the right subtree.
        }
    }

    // Update height directly
    root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // Update height.
    int blc = getBalance(root);
    
    if(blc > 1 && data < root->left->data){
        return rightRotate(root);
    }
    if(blc < -1 && data > root->right->data){
        return leftRotate(root);
    }
    if(blc > 1 && data > root->left->data){
        return rightRotate(root);
    }
    if(blc < -1 && data < root->right->data){
        return leftRotate(root);
    }
    return root;
}



Node* find(Node* root, int data){
    if(root == NULL) return root;
    if(data > root->data) find(root->right, data);
    else if(data < root->data) find(root->left, data);
    else return root;
}

void checkout(Node *n)
{
    if (n == NULL)
        return;
    checkout(n->left);
    checkout(n->right);
    free(n);
}

void inOrder(Node *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("=> %d(%d)[%d]", root->data, root->height, getBalance(root));
    inOrder(root->right);
}

int sum(Node* root){
    if(root == NULL) return 0;
    return root->data + sum(root->left) + sum(root->right);
}

