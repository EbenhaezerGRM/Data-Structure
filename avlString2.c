#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    struct tnode * left;
    struct tnode * right;
    int height;
    char userName[100];
    char hobby[100];
};

struct tnode * root = NULL;

struct tnode * create(char userName[], char hobby[]){
    struct tnode * newNode = (struct tnode *)malloc(sizeof(struct tnode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    strcpy(newNode->userName, userName);
    strcpy(newNode->hobby, hobby);

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

struct tnode * insert(struct tnode * curr, char userName[], char hobby[]){
    char userNameTemp[110];
    int num = rand() % 999 + 100;
    sprintf(userNameTemp, "%s%d", userName, num);

    if(curr == NULL){
        return create(userNameTemp, hobby);
    }
    if(strcmp(userNameTemp, curr->userName) < 0){
        curr->left = insert(curr->left, userName, hobby);
    }
    else if(strcmp(userNameTemp, curr->userName) > 0){
        curr->right = insert(curr->right, userName, hobby);
    }
    else{
        return curr;
    }

    curr->height = 1 + max(height(curr->left), height(curr->right));
    int balance = getBalance(curr);

    if(balance > 1 && strcmp(userNameTemp, curr->left->userName) < 0){
        return rightRotate(curr);
    }
    if(balance < -1 && strcmp(userNameTemp, curr->right->userName) > 0){
        return leftRotate(curr);
    }
    if(balance > 1 && strcmp(userNameTemp, curr->left->userName) > 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr); 
    }
    if(balance < -1 && strcmp(userNameTemp, curr->right->userName) < 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void search(struct tnode * curr, char userName[]){
    if(curr == NULL){
        printf("Not Found\n");
        return;
    }
    else if(strcmp(userName, curr->userName) < 0){
        search(curr->left, userName);
    }
    else if(strcmp(userName, curr->userName) > 0){
        search(curr->right, userName);
    }
    else if(strcmp(userName, curr->userName) == 0){
        printf("Show: %s\n", curr->userName);
        printf("Hobbies: %s", curr->hobby);
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

struct tnode * del(struct tnode * curr, char userName[]){
    if(curr == NULL){
        return NULL;
    }
    if(strcmp(userName, curr->userName) < 0 && curr->left == NULL || strcmp(userName, curr->userName) > 0 && curr->right == NULL){
        return curr;
    }
    else if(strcmp(userName, curr->userName) < 0){
        curr->left = del(curr->left, userName);
    }
    else if(strcmp(userName, curr->userName) > 0){
        curr->right = del(curr->right, userName);
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
            strcpy(curr->userName, tmp->userName);
            curr->left = del(curr->left, tmp->userName);
        }
    }
    curr->height = 1 + max(height(curr->left), height(curr->right));
    int balance = getBalance(curr);

    if(balance > 1 && getBalance(curr->left) >= 0){
        return rightRotate(curr);
    }
    if(balance < -1 && getBalance(curr->left) <= 0){
        return leftRotate(curr);
    }
    if(balance > 1 && getBalance(curr->left) < 0){
        curr->left = leftRotate(curr->left);
        return rightRotate(curr); 
    }
    if(balance < -1 && getBalance(curr->left) > 0){
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

void inorder(struct tnode * curr){
    if(curr->left != NULL){
        inorder(curr->left);
    }
    printf("%-10s %s\n", curr->userName, curr->hobby);
    if(curr->right != NULL){
        inorder(curr->right);
    }
}

int main() {
    char option[100];
    char userName[100];
    char hobby[100];

    do {
        scanf("%s", option);
        
        if(strcmp(option, "insert") == 0){
            scanf("%[^-]-%[^\n]", userName, hobby);
            root = insert(root, userName, hobby);
            printf(">> Insert operation of %s completed. <<\n", userName);
        } 
        else if(strcmp(option, "show_all") == 0){
            printf("Username  - Hobbies\n");
            inorder(root);
            printf(">> Show all operation completed. <<\n");
        } 
        else if(strcmp(option, "delete") == 0){
            scanf("%s", userName); 
            root = del(root, userName);
            printf(">> delete operation completed. <<\n");
        } 
        else if(strcmp(option, "search") == 0){
            scanf("%s", userName); 
            search(root, userName);
            printf(">> delete operation completed. <<\n");
        } 
        else if(strcmp(option, "exit") != 0){
            printf("Invalid option\n");
        }
    }while(strcmp(option, "exit") != 0);
    printf("End Of Application\n");
    return 0;
}