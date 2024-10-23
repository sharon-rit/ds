#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node *head = NULL;
//node *tail = NULL;

bool isListEmpty(bool should_print) {
    if(head == NULL) {
	if(should_print) printf("List is empty!");
        return true;
    }

    return false;
}

node * createNode(int value) {
    node * newnode = (node *) malloc(sizeof(node));
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

void insertAtBeginning(int);
void insertAtEnd(int);
void insertAtPosition(int,int);
void display();
void deleteFromBeginning();
void deleteFromEnd();
//void deleteAtPosition(int);
void search(int);


void deleteAtPosition(int position) {
    if(isListEmpty(true)) return;

    node *temp = head;

    if(temp->right == NULL || position <= 1) {
	deleteFromBeginning();
	return;
    }

    int index = 1;
    while(temp->right != NULL){
	if(index == position){
	    temp->right->left = temp->left;
	    temp->left->right = temp->right;
	    printf("%d was deleted from the list at position %d",temp->data,position);
	    free(temp);
	    return;
	}
	index++;
	temp = temp->right;
    }

    if(position > index) printf("Position if out of bounds!");

}

void insertAtPosition(int value, int position) {

    if(isListEmpty(false) || position <= 1) {
	insertAtBeginning(value);
	return;
    }

    node *newnode = createNode(value);

    int index = 1;
    node *current = head;

    while(current->right != NULL) {
	if(index == position-1) {
	    current->right->left = newnode;
	    newnode->right = current->right;
	    newnode->left = current;
	    current->right = newnode;

	    printf("%d was entered into position %d",newnode->data, position);
	}
	index++;
	current = current->right;
    }

    if(index > position) printf("Position is out of bounds!");
}

void search(int value) {
    int position = 1;
    node *current = head;
    while(current != NULL) {
	if(current->data == value) {
	    printf("%d was found in list at position %d",current->data,position);
	    return;
	}
	position++;
	current = current->right;
    }

    printf("%d is not in the list!",value);
}

void deleteFromBeginning(){
   if(isListEmpty(true)) return;

    node *temp = head;

    if(temp->right == NULL) {
	head = NULL;
    } else {
        temp->right->left = NULL;
        head = temp->right;
    }

    printf("%d was deleted from the list start",temp->data);
    free(temp);
}

void deleteFromEnd() {
    if(isListEmpty(true)) return;

    node *temp = head;

    if(temp->right == NULL) {
	deleteFromBeginning();
	return;
    }

    while(temp->right != NULL) {
	temp = temp->right;
    }

    //update tail
    temp->left->right = NULL;
    printf("%d was deleted from the list end",temp->data);
    free(temp);

}

void display(){
    if(isListEmpty(true)) return;

    node *current = head;
    while(current != NULL) {

        //if(current->right != NULL || current->left == NULL) printf("%d -> ",current->data);
        //if(current->right == NULL || current->left != NULL)  printf("NULL");

	printf("%d -> ",current->data);

	current = current->right;
    }
}

void insertAtEnd(int value) {
    if(isListEmpty(false)) {
	insertAtBeginning(value);
	return;
    }

    node * newnode = createNode(value);

    node * current = head;

    while(current->right != NULL) {
	current = current->right;
    }

    newnode->left = current;
    newnode->right = NULL; // already defined;
    current->right = newnode;

    //tail = newnode;
    printf("%d was entered into the end of the list",current->right->data);
}

void insertAtBeginning(int value){
    node * newnode = createNode(value);

    newnode->left = NULL; //already defined.
    newnode->right = head; // head contains the address of the first node or NULL if empty.

    if(!isListEmpty(false)) head->left = newnode; // if list has atleast 1 element, then update that node's left address as newnode's address

    head = newnode;
    printf("%d was entered into the beginning of the list",head->data);
}

int getValue(){
    int value;
    printf("Enter the value: ");
    scanf("%d", &value);
    return value;
}

int getPosition(){
    int value;
    printf("Enter the position: ");
    scanf("%d",&value);
    return value;
}

int main() {

    int choice;
    while(true){
	printf("\n\nSelect the Operation to Perform: \n1)InsertAtBeginning \n2)InsertAtEnd \n3)InsertAtPosition \n4)Display \n5)DeleteFromBeginning \n6)DeleteFromEnd \n7)DeleteAtPosition \n8)Search \n9)Quit: ");
	scanf("%d",&choice);

        switch(choice){
	    case 1: insertAtBeginning(getValue()); break;
	    case 2: insertAtEnd(getValue()); break;
	    case 3: insertAtPosition(getValue(), getPosition()); break;
	    case 4: display(); break;
	    case 5: deleteFromBeginning(); break;
	    case 6: deleteFromEnd(); break;
	    case 7: deleteAtPosition(getPosition()); break;
	    case 8: search(getValue()); break;
	    case 9: printf("Qutting Program...\n"); exit(0);
	    default: printf("Invalid Input! Try again.\n");
	}
    }

    return 0;
}
