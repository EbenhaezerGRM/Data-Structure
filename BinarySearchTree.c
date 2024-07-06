#include <stdio.h>
#include <stdlib.h>

struct tnode{
	int value;
	struct tnode * left;
	struct tnode * right;
};

struct tnode * root = NULL;

struct tnode * create(int value){
	struct tnode * newNode = (struct tnode *)malloc(sizeof(struct tnode));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
};

void insert(struct tnode * curr, int value){
	if(root == NULL){
		root = create(value);
	}
	else{
		if(value < curr->value && curr->left == NULL){
			curr->left = create(value);
		}
		else if(value > curr->value && curr->right == NULL){
			curr->right = create(value);
		}
		else if(value < curr->value){
			insert(curr->left, value);
		}
		else if(value > curr->value){
			insert(curr->right, value);
		}
	}
}

void prefix(struct tnode * curr){
	if(curr != NULL){
		printf("%d ", curr->value);
		prefix(curr->left);
		prefix(curr->right);
	}
}

void infix(struct tnode * curr){
	if(curr != NULL){
		infix(curr->left);
		printf("%d ", curr->value);
		infix(curr->right);
	}
}

void postfix(struct tnode * curr){
	if(curr != NULL){
		postfix(curr->left);
		postfix(curr->right);
		printf("%d ", curr->value);
	}
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

struct tnode * getMaxLeft(struct tnode * curr){
	struct tnode * iter = curr->left;
	while(iter->right){
		iter = iter->right;
	}
	return iter;
}

struct tnode * del(struct tnode * curr, int value){
	if(root == NULL){
		return NULL;
	}
	if(value < curr->value && curr->left == NULL || value > curr->value && curr->right == NULL){
		return curr;
	}
	if(value < curr->value){
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
			struct tnode * tmp = getMaxLeft(curr);
			curr->value = tmp->value;
			curr->left = del(curr->left, tmp->value);
		}
	}
	return curr;
}

void getMax(){
	struct tnode * curr;
	while(curr->right != NULL){
		curr = curr->right;
	}
	printf("%d", curr->value);
}

int main(){
	insert(root, 3);
	insert(root, 1);
	insert(root, 6);
	insert(root, 8);
	insert(root, 5);
	insert(root, 12);
	insert(root, 9);

	infix(root);
	printf("\n");

	root = del(root, 12);

	struct tnode * searchValue = search(root, 12);
	if(searchValue != NULL){
		printf("Value %d Found\n", searchValue->value);
	}
	else{
		printf("Value Not Found\n");
	}

	infix(root);

	getMax();

	return 0;
}