#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node * next;
};

struct node * head = NULL;
struct node * tail = NULL;

struct node * create(int value){
    struct node * newNode = (struct node *)malloc(sizeof(struct node));

    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertHead(int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
    }
    else{
        struct node * newNode = create(value);
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
        tail = newNode;
    }
}

void insertAfterMid(int key, int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
        return; 
    }

    struct node * curr = head;
    struct node * temp = NULL;
    
    int flag = 0;
    while(curr != NULL){
        if(curr->value == key){
            temp = curr;
            flag = 1;
            break;
        }
        curr = curr->next;
    }

    if(flag == 0){
        printf("%d Not Found\n", value);
        return; 
    }

    struct node * newNode = create(value);
    newNode->next = temp->next; 
    temp->next = newNode; 
}

void insertBeforeMid(int key, int value){
    if(head == NULL && tail == NULL){
        head = create(value);
        tail = head;
        return;
    }

    struct node * curr = head;
    struct node * temp = NULL;
    
    int flag = 0;
    while(curr != NULL){
        if(curr->value == key){
            temp = curr;
            flag = 1;
            break;
        }
        curr = curr->next;
    }

    if(flag == 0){
        printf("%d Not Found\n", value);
        return;
    }

    struct node * newNode = create(value);
    newNode->next = temp;
    if(temp != head){
        curr = head;
        while(curr->next != temp){
            curr = curr->next;
        }
        curr->next = newNode;
    }
    else{
        head = newNode;
    }
}

void printHead(){
    struct node * curr = head;
    while(curr != NULL){
        printf("%d", curr->value);
        if(curr->next != NULL){
            printf(" -> ");
        }
        curr = curr->next;
    }
}

void printTail(struct node * curr){
    if(curr == NULL){
        return;
    }
    printf("%d", curr->value);
    if(curr->next != NULL){
        printf(" -> ");
    }
    printTail(curr->next);
}

void del(int value){
	struct node * curr = head;
	if(head->value == value){
		head = head->next;
		free(curr);
	}
	else{
		while(curr->next->value != value){
			curr = curr->next;
		}	
		struct node * del = curr->next;
		curr->next = del->next;
		free(del);
	}
}

void search(int value){
    struct node * curr = head;
    while(curr->next != NULL){
        if(curr->value == value){
            printf("%d Found\n", value);
        }
        curr = curr->next;
    }
}

int main(){
    insertTail(5);
    insertTail(10);
    insertTail(15);

    printHead();
    printf("\n");

    insertAfterMid(15, 20);
    printHead();
    printf("\n");

    insertBeforeMid(15, 12);
    printHead();
    printf("\n");

    search(12);

    del(12);

    printHead();
    printf("\n");
    
    return 0;
}
