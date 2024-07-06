#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
    char book[10];
    int year;
    struct tnode * left;
    struct tnode * right;
};

struct tnode * root = NULL;

struct tnode * create(char book[], int year){
    struct tnode * newNode = (struct tnode *)malloc(sizeof(struct tnode));
    strcpy(newNode->book, book);
    newNode->year = year;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void insert(struct tnode * curr, char book[], int year){
    if(root == NULL){
        root = create(book, year);
    }
    else{
        if((strcmp(book, curr->book) < 0 && curr->left == NULL)){
            curr->left = create(book, year);
        }
        else if((strcmp(book, curr->book) > 0 && curr->right == NULL)){
            curr->right = create(book, year);
        }
        else if(strcmp(book, curr->book) < 0){
            insert(curr->left, book, year);
        }
        else if(strcmp(book, curr->book) > 0){
            insert(curr->right, book, year);
        }
    }
}

void prefix(struct tnode * curr){
    if(curr != NULL){
        printf("Book: %s\n", curr->book);
        printf("Year: %d\n", curr->year);
        prefix(curr->left);
        prefix(curr->right);
    }
}

void infix(struct tnode * curr){
    if(curr != NULL){
        infix(curr->left);
        printf("Book: %s\n", curr->book);
        printf("Year: %d\n", curr->year);
        infix(curr->right);
    }
}

void postfix(struct tnode * curr){
    if(curr != NULL){
        printf("Book: %s\n", curr->book);
        printf("Year: %d\n", curr->year);
        postfix(curr->left);
        postfix(curr->right);
    }
}

struct tnode * search(struct tnode * curr, char book[]){
    if(curr == NULL){
        return NULL;
    }
    else if(strcmp(book, curr->book) < 0){
        search(curr->left, book);
    }
    else if(strcmp(book, curr->book) > 0){
        search(curr->right, book);
    }
    else if(strcmp(book, curr->book) == 0){
        return curr;
    }
}

struct tnode * getMaxLeft(struct tnode * curr){
    struct tnode * iter = curr->left;
    while(iter->right){
        iter = iter->right;
    }
    return iter;
}

struct tnode * del(struct tnode * curr, char book[]){
    if(root == NULL){
        return NULL;
    }
    if((strcmp(book, curr->book) < 0 && curr->left == NULL) || (strcmp(book, curr->book) > 0 && curr->right == NULL)){
        return curr;
    }
    if((strcmp(book, curr->book) < 0)){
        curr->left = del(curr->left, book);
    }
    else if((strcmp(book, curr->book) > 0)){
        curr->right = del(curr->right, book);
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
            struct tnode * tmp = getMaxLeft(curr);
            strcpy(curr->book, tmp->book);
            curr->left = del(curr->left, tmp->book);
        }
    }
    return curr;
}

int main(){
    insert(root, "Perahu", 2020);
    insert(root, "Kertas", 2023);
    insert(root, "Miniatur", 2024);

    prefix(root);

    struct tnode * searchValue = search(root, "Kertas");
    if(searchValue != NULL){
		printf("Value %s Found\n", searchValue->book);
	}
	else{
		printf("Value Not Found\n");
	}
    root = del(root, "Kertas");
    prefix(root);

    return 0;
}
