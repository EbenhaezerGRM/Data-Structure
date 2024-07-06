#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    struct tnode * left;
    struct tnode * right;
    int height;
    char title[100];
    int year;
};

struct tnode * root = NULL;

struct tnode * create(char title[], int year){
    struct tnode * newNode = (struct tnode *)malloc(sizeof(struct tnode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    strcpy(newNode->title, title);
    newNode->year = year;

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

int height(struct tnode * node){
    if(node == NULL){
        return 0;
    }
    else{
        return node->height;
    }
}

int getBalance(struct tnode * node){
    if(node == NULL){
        return 0;
    }
    else{
        return height(node->left) - height(node->right);
    }
}

struct tnode * leftRotate(struct tnode * node){
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

struct tnode * insert(struct tnode * curr, char title[], int year){
    if(curr == NULL){
        return create(title, year);
    }
    if(strcmp(title, curr->title) < 0){
        curr->left = insert(curr->left, title, year);
    }
    else if(strcmp(title, curr->title) > 0){
        curr->right = insert(curr->right, title, year);
    }
    else{
        return curr;
    }

    curr->height = 1 + max(height(curr->left), height(curr->right));
    int balance = getBalance(curr);

    if(balance > 1 && strcmp(title, curr->left->title) < 0){
        return rightRotate(curr);
    }
    if(balance < -1 && strcmp(title, curr->right->title) > 0){
        return leftRotate(curr);
    }
    if(balance > 1 && strcmp(title, curr->left->title) > 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    if(balance < -1 && strcmp(title, curr->right->title) < 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void search(struct tnode * curr, char title[]){
    if(curr == NULL){
        printf("Title: %s Is Not Found\n", title);
        return;
    }
    else if(strcmp(title, curr->title) < 0){
        search(curr->left, title);
    }
    else if(strcmp(title, curr->title) > 0){
        search(curr->right, title);
    }
    else if(strcmp(title, curr->title) == 0){
        printf("Title: %s, Year: %d Is Found\n", curr->title, curr->year);
        return;
    }
}

struct tnode * maxLeft(struct tnode * curr){
    struct tnode * iter = curr->left;
    while(iter->right != NULL){
        iter = iter->right;
    }
    return iter;
}

struct tnode * del(struct tnode * curr, char title[]){
    if(curr == NULL){
        return NULL;
    }
    if(strcmp(title, curr->title) < 0 && curr->left == NULL || strcmp(title, curr->title) > 0 && curr->right == NULL){
        return curr;
    }
    else if(strcmp(title, curr->title) < 0){
        curr->left = del(curr->left, title);
    }
    else if(strcmp(title, curr->title) > 0){
        curr->right = del(curr->right, title);
    }
    else{
        if(curr->left == NULL && curr->right == NULL){
            free(curr);
            return NULL;
        }
        else if(curr->left == NULL){
            return curr->right;
        }
        else if(curr->right ==  NULL){
            return curr->left;
        }
        else{
            struct tnode * tmp = maxLeft(curr);
            strcpy(curr->title, tmp->title);
            curr->left = del(curr->left, tmp->title);
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
    printf("Title: %s, Year: %d\n", curr->title, curr->year);
    if(curr->right != NULL){
        inorder(curr->right);
    }
}

int main(){
    root = insert(root, "Music1", 2004);
    root = insert(root, "Music2", 2005);
    root = insert(root, "Music3", 2006);
    root = insert(root, "Music4", 2007);
    root = insert(root, "Music5", 2008);

    inorder(root);
    printf("\n");

    search(root, "Music3");
    root = del(root, "Music3");
    printf("\n");

    search(root, "Music3");
    printf("\n");

    inorder(root);
    return 0;
}