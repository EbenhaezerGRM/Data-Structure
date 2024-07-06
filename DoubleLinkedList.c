#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node * next;
    struct node * prev;
};

struct node * head = NULL;
struct node * tail = NULL;

struct node * create(int value){
    struct node * newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void insertHead(int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
    }
    else{
        struct node * newNode = create(value);
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}

void insertTail(int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
    }
    else{
        struct node * newNode = create(value);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void insertBeforeValue(int search, int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
    }
    else{
        struct node * newNode = create(value);
        struct node * curr = head;

        if(curr->value == search){
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            return;
        }
        while(curr->next->value != search){
            curr = curr->next;
        }
        curr->next->prev = newNode;
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next = newNode;
    }
}

void insertAfterValue(int search, int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
    }
    else{
        struct node * curr = head;
        struct node * newNode = create(value);

        while(curr->value != search){
            curr = curr->next;
        }
        if(curr->next != NULL){
            curr->next = newNode;
            newNode->prev = curr;
            newNode->next = curr->next->next;
            curr->next->prev = newNode;
        }
        if(curr->next == NULL && curr->value == tail->value){
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
}

void printHead(){
    if(head == NULL){
        printf("Empty List\n");
    }

    struct node * curr = head;
    while(curr != NULL){
        printf("%d", curr->value);
        if(curr->next != NULL){
            printf(" -> ");
        }
        curr = curr->next;
    }
    printf("\n");
}

void printTail(){
    if(head == NULL){
        printf("Empty List\n");
    }

    struct node * curr = tail;
    while(curr != NULL){
        printf("%d", curr->value);
        if(curr->prev != NULL){
            printf(" -> ");
        }
        curr = curr->prev;
    }
    printf("\n");
}

void search(int value){
    struct node * curr = head;
    while(curr != NULL){
        if(curr->value == value){
            printf("%d Found\n", value);
            return;
        }
        curr = curr->next;
    }
    printf("%d Not Found\n", value);
}

void del(int value){
    struct node * curr = head;
    while(curr != NULL){
        if(curr->value == value){
            if(head->value == value && head->next == NULL){
                free(head);
                head = NULL;
                tail = NULL;
                printf("%d Deleted\n", value);
                return;
            }
            else if(head->value == value && head->next != NULL){
                head = head->next;
                free(head->prev);
                head->prev = NULL;
                printf("%d Deleted\n", value);
                return;
            }
            else if(tail->value == value && tail->prev != NULL){
                tail = tail->prev;
                free(tail->next);
                tail->next = NULL;
                printf("%d Deleted\n", value);
                return;
            }
            else{
                struct node * curr = head;
                while(curr->next->value != value){
                    curr = curr->next;
                }
                struct node * a = curr;
                struct node * del = curr->next;
                struct node * b = curr->next->next;

                a->next = b;
                b->prev = a;
                free(del);
                printf("%d Deleted\n", value);
                return;
            }
            return;
        }
        curr = curr->next;
    }
    printf("%d Not Found\n", value);
}

void delAll(){
    while(head != NULL){
        del(head->value);
    }
}
 
int main(){
    system("cls");

    insertTail(5);
    insertTail(10);
    insertTail(15);
    insertTail(20);
    insertTail(25);
    insertTail(30);
    insertTail(35);
    insertTail(40);

    printHead();

    search(25);
    
    del(25);

    search(25);

    printTail();

    insertBeforeValue(30, 25);

    printHead();
    
    insertAfterValue(40, 45);

    printHead();

    return 0;
}