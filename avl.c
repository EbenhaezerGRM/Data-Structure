#include <stdio.h>
#include <stdlib.h>

struct tnode{
    struct tnode * left;
    struct tnode * right;
    int height;
    int value;
};

struct tnode * root = NULL;

struct tnode * create(int value) {
    struct tnode * newNode = (struct tnode *)malloc(sizeof(struct tnode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->value = value;

    return newNode;
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int height(struct tnode * node) {
    if(node == NULL){
        return 0;
    }
    else{
        return node->height;
    }
}

int getBalance(struct tnode * node) {
    if(node == NULL){
        return 0;
    }
    else{
        return height(node->left) - height(node->right);
    }
}

struct tnode * leftRotate(struct tnode * node) {
    struct tnode * a = node->right;
    struct tnode * b = a->left;

    a->left = node;
    node->right = b;

    a->height = 1 + max(height(a->left), height(a->right));
    node->height = 1 + max(height(node->left), height(node->right));

    return a;
}

struct tnode * rightRotate(struct tnode * node){
    struct tnode * a = node->left;
    struct tnode * b = a->right;

    a->right = node;
    node->left = b;

    a->height = 1 + max(height(a->left), height(a->right));
    node->height = 1 + max(height(node->left), height(node->right));

    return a;
}

struct tnode * insert(struct tnode * curr, int value) {
    if(curr == NULL){
        return create(value);
    }
    if(value < curr->value){
        curr->left = insert(curr->left, value);
    } 
    else if(value > curr->value){
        curr->right = insert(curr->right, value);
    } 
    else{
        return curr;
    }

    curr->height = 1 + max(height(curr->left), height(curr->right));
    int balance = getBalance(curr);

    if(balance > 1 && value < curr->left->value){
        return rightRotate(curr);
    }
    if(balance < -1 && value > curr->right->value){
        return leftRotate(curr);
    }
    if(balance > 1 && value > curr->left->value){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(balance < -1 && value < curr->right->value){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

struct tnode * search(struct tnode * curr, int value){
    if(curr == NULL){
        return NULL;
    }
    else if(value < curr->value){
        search(curr->left, value);
    }
    else if(value > curr->value){
        search(curr->right, value);
    }
    else if(value == curr->value){
        return curr;
    }
}

struct tnode * maxLeft(struct tnode * curr){
    struct tnode * iter = curr->left;
    while(iter->right != NULL){
        iter = iter->right;
    }
    return iter;
}

struct tnode * del(struct tnode * curr, int value){
    if(curr == NULL){
        return NULL;
    }
    if(value < curr->value && curr->left == NULL || value > curr->value && curr->right == NULL){
        return curr;
    }
    else if(value < curr->value){
        curr->left = del(curr->left, value);
    }
    else if(value > curr->value){
        curr->right = del(curr->right, value);
    }
    else{
        if(curr->left == NULL && curr->right == NULL){
            free(curr);
            return NULL;
        }
        else if(curr->left == NULL){
            return curr->right;
        }
        else if(curr->right == NULL){
            return curr->left;
        }
        else{
            struct tnode * tmp = maxLeft(curr);
            curr->value = tmp->value;
            curr->left = del(curr->left, tmp->value);
        }
    }

    curr->height = 1 + max(height(curr->left), height(curr->right));
    int balance = getBalance(curr);

    if(balance > 1 && getBalance(curr->left) >= 0){
        return rightRotate(curr);
    }
    if(balance < -1 && getBalance(curr->right) <= 0){
        return leftRotate(curr);
    }
    if(balance > 1 && getBalance(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(balance < -1 && getBalance(curr->right) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void inorder(struct tnode * curr){
    if(curr->left != NULL){
        inorder(curr->left);
    }
    printf("%d ", curr->value);
    if(curr->right != NULL){
        inorder(curr->right);
    }    
}

int main(){
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 6);
    root = insert(root, 11);

    inorder(root);

    root = del(root, 10);
    printf("\n");
    inorder(root);
    
    return 0;
}