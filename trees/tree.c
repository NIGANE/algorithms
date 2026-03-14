#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

Node* createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Memory Allocation Failed");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
Node* insertNode(Node* root, int data){
    if(root == NULL){
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else if(data > root->data)
    {
        root->right = insertNode(root->right, data);
    }else{
        return root;
    }

    return root;
}
Node* insertMaxHeap(Node* root, int data)
{

}


Node *search(Node *root, int *target)
{
    if (root == NULL)
        return NULL;
    if (root->data == *target)
        return root;
    if (*target < root->data)
    {
        return search(root->left, target);
    }
    else
    {
        return search(root->left, target);
    }
}
Node* findMin(Node* root);
Node *deleteNode(Node *root, int target)
{
    if (root == NULL)
        return NULL;

    if (target < root->data)
    {
        root->left = deleteNode(root->left, target);
    }
    else if (target > root->data)
    {
        root->right = deleteNode(root->right, target);
    }
    else
    {
        // Case 1: No children
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2: One child (right)
        else if (root->left == NULL)
        {
            Node *temp = root;
            root = root->right;
            free(temp);
            return root;
        }
        // Case 2: One child (left)
        else if (root->right == NULL)
        {
            Node *temp = root;
            root = root->left;
            free(temp);
            return root;
        }
        // Case 3: Two children
        else
        {
            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

Node* findMin(Node* root){
    if(root->left == NULL) return root;
    else return findMin(root->left);
}

void checkout(Node* n){
    if(n == NULL) return;
    checkout(n->left);
    checkout(n->right);
    free(n);
}

// T R A V E R S A L :
void preOrder(Node* root){
    if(root == NULL)return;
    printf("=> %d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("=> %d ", root->data);
    inOrder(root->right);
}

void postOrder(Node* root){
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("=> %d ", root->data); 
}
//////////////////////
int isBstUtil(Node* root, int* prev){
    if (root == NULL) return 1;

    if(!isBstUtil(root->left, prev)) return 0;
    if(root->data <= *prev) return 0;
    *prev = root->data;
    return isBstUtil(root->right, prev);

}
int isBST(Node* root){
    if(root == NULL) return 1;
    int prev = INT_MIN;
    return isBstUtil(root, &prev);
}
//    print using deep first search
void print_depth_first(Node* node){
    Node* process_stack[100];
    size_t process_stack_num = 0;
    process_stack[0] = node;
    process_stack_num++;
    while(process_stack_num > 0){
        Node* curr = process_stack[--process_stack_num];
        printf("%d ", curr->data);

        if(curr->right != NULL){
            process_stack[process_stack_num++] = curr->right;
        }
        if(curr->left != NULL){
        process_stack[process_stack_num++] = curr->left;
        }
    }
}

//    deep first search :
int dfs(Node *node, int data)
{
    int founded;

    if (!node)
        return (0);
    if (node->data == data)
    {
        printf("found: %d\n", node->data);    
        return (1);
    }
    founded = 0;
    if (node->left)
        founded = dfs(node->left, data);
    if (founded == 1)
        return (founded);
    if (node->right)
        founded = dfs(node->right, data);
    return (founded);
}
//    print using breath first search :
void print_breath_first(Node *node)
{
    Node* process_queu[100];
    size_t reader_num = 0;
    size_t add_num = 0;
    process_queu[add_num++] = node;
    while(add_num > reader_num){
        Node* curr = process_queu[reader_num++];
        printf("%d ", curr->data);
        if(curr->left != NULL){
            process_queu[add_num++] = curr->left;
        }
        if(curr->right != NULL){
            process_queu[add_num++] = curr->right;
        }
    }
}
//    breath first search :
int bfs(Node *node, int data)
{
    Node* process_queu[100];
    size_t reader_num;
    size_t add_num;
    Node*   cur;

    reader_num = 0;
    add_num = 0;
    cur = node;
    process_queu[add_num++] = node;
    while(add_num > reader_num){
        if (process_queu[reader_num]->data == data)
        {
            printf("founded: %d\n", process_queu[reader_num]->data);
            return (1);
        }
        cur = process_queu[reader_num++];
        if(cur->left){
            process_queu[add_num++] = cur->left;
        }
        if(cur->right){
            process_queu[add_num++] = cur->right;
        }
    }
    return (0);
}

int isFull(Node* root)
{
#define MAX_NODES 256 // make big enough or realloc

        void
        treeToArray(Node * root, int out[], int *outSize)
    {
        *outSize = 0;
        if (root == NULL)
            return;

        Node *q[MAX_NODES];
        int front = 0, rear = 0;

        q[rear++] = root;

        while (front < rear)
        {
            Node *cur = q[front++];
            out[(*outSize)++] = cur->data; // copy key

            if (cur->left)
                q[rear++] = cur->left;
            if (cur->right)
                q[rear++] = cur->right;
        }
    }

    if(root == NULL) return 1;
    if(root->left == NULL && root->right == NULL) return 1;
    if(root->left && root->right) return isFull(root->left) && isFull(root->right);
    return 0;
}

int isComplete(Node* root){
    if(root == NULL) return 1;

    Node* holder_queue[100];
    int add = 0;
    int read = 0;

    holder_queue[add++] = root;
    int foundNull = 0;

    while(add > read){
        Node* curr = holder_queue[read++];

        if(curr->left){
            if(foundNull > 0) return 0;
            holder_queue[add++] = curr->left;
        }else{
            foundNull = 1;
        }


        if (curr->right)
        {
            if (foundNull > 0)
                return 0;
            holder_queue[add++] = curr->right;
        }
        else
        {
            foundNull = 1;
        }
    }
    return 1;
}

int isMaxHeap(Node* root)
{
    if (root == NULL)
        return 1;

    Node *holder_queue[100];
    int add = 0;
    int read = 0;

    holder_queue[add++] = root;
    int foundNull = 0;

    while (add > read)
    {
        Node *curr = holder_queue[read++];

        if (curr->left)
        {
            if (foundNull > 0 || curr->data < curr->left->data)
                return 0;
            holder_queue[add++] = curr->left;
        }
        else
        {
            foundNull = 1;
        }

        if (curr->right)
        {
            if (foundNull > 0 || curr->data < curr->right->data)
                return 0;
            holder_queue[add++] = curr->right;
        }
        else
        {
            foundNull = 1;
        }
    }
    return 1;
}

int isMinHeap(Node *root)
{
    if (root == NULL)
        return 1;

    Node *holder_queue[100];
    int add = 0;
    int read = 0;

    holder_queue[add++] = root;
    int foundNull = 0;

    while (add > read)
    {
        Node *curr = holder_queue[read++];

        if (curr->left)
        {
            if (foundNull > 0 || curr->data > curr->left->data)
                return 0;
            holder_queue[add++] = curr->left;
        }
        else
        {
            foundNull = 1;
        }

        if (curr->right)
        {
            if (foundNull > 0 || curr->data > curr->right->data)
                return 0;
            holder_queue[add++] = curr->right;
        }
        else
        {
            foundNull = 1;
        }
    }
    return 1;
}


int main(){
    // Complete:
    Node* tree1 = createNode(40);
    tree1 = insertNode(tree1, 30);
    tree1 = insertNode(tree1, 20);
    tree1 = insertNode(tree1, 35);
    tree1 = insertNode(tree1, 50);
    // Fulll:
    Node *tree2 = createNode(40);
    tree2 = insertNode(tree2, 20);
    tree2 = insertNode(tree2, 45);
    tree2 = insertNode(tree2, 10);
    tree2 = insertNode(tree2, 30);
    tree2 = insertNode(tree2, 41);
    tree2 = insertNode(tree2, 50);
    // None:
    Node *tree3 = createNode(70);
    tree3 = insertNode(tree3, 61);
    tree3 = insertNode(tree3, 80);
    tree3 = insertNode(tree3, 75);
    tree3 = insertNode(tree3, 90);
    tree3 = insertNode(tree3, 20);
}
