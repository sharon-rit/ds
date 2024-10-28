#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *head = NULL;
//node *tail = NULL;

int getValue() {
    int value;

    printf("Enter the value: ");
    scanf("%d",&value);

    return value;
}

int getPosition() {
    int value;

    printf("Enter the Position: ");
    scanf("%d",&value);

    return value;
}

bool isListEmpty(bool should_print) {
    if(head == NULL) {
        if(should_print) printf("List is empty!\n");
	return true;
    }

    return false;
}

node* createNode(int value) {
    node *newnode = (node *) malloc(sizeof(node));

    newnode->data = value;
    newnode->next = NULL;

    return newnode;
}

void search(int value) {
    node *temp = head;

    while(temp != NULL) {
	if(temp->data == value) {
	    printf("Value found!!!");
	    return;
	}
	temp = temp->next;
    }

    printf("%d was not found in the list",value);
}

void deleteFromBeginning();

void deleteAtPosition(int position) {
    int index = 2;
    node *temp = head;

    if(isListEmpty(true)) return;

    if(temp->next == NULL || position == 1) {
    	deleteFromBeginning();
        return;
    }

    while(temp->next != NULL) {
    	if(index == position) {
	    printf("%d was deleted from the list at position %d", temp->next->data, position);
            node *ptr = temp->next->next;
	    free(temp->next);
	    temp->next = ptr;
	    break;
	}
	index++;
	temp = temp->next;
    }
    
    if(index > position) printf("position is out of bounds!"); 
}

void deleteFromBeginning() {

    if(isListEmpty(true)) return;

    node *temp = head;

    printf("%d was deleted from the list Beginning",temp->data);
    head = temp->next;
    free(temp);
}

void deleteFromEnd(){

    if(isListEmpty(true)) return;

    node *temp = head;

    if(temp->next == NULL) {
        printf("%d was deleted from the List end", temp->data);
        head = temp->next;
        free(temp);
        return;
    }

    while(temp->next->next != NULL) {
	temp = temp->next;
    }

    printf("%d was deleted from the list end", temp->next->data);
    free(temp->next);
    temp->next = NULL;

}

void displayList() {
    node *current = head;

    if(!isListEmpty(true)) {
	while(current != NULL) {

	    if(current->next != NULL) printf("%d -> ",current->data);
	    else printf("%d",current->data);

            current = current->next;
    	}

    	printf("\n");
    }
}

void insertAtBeginning(int value) {
    node *newnode = createNode(value);

    newnode->next = head;
    head = newnode;

   printf("%d was Entered into the list at Beginning", head->data);

}

void insertAtEnd(int value) {
    node *newnode = createNode(value);

    node *current = head;

    if(isListEmpty(false)) {
        printf("Inserting %d to list end",newnode->data);
	head = newnode;
        return;
    }

    while(current->next != NULL) {
        current = current->next;
    }

    current->next = newnode;

    printf("%d was entered into the list End",newnode->data);
    return;
}

void insertAtPosition(int value, int position) {
    int index = 2;
    node *newnode = createNode(value);

    node *current = head;

    if(isListEmpty(false) || position <= 1){
        newnode->next = head;
	head = newnode;
	printf("Inserting %d to position 1",newnode->data);
	return;
    }

    while(current->next != NULL) {
	if(index == position){
	    newnode->next = current->next;
	    current->next = newnode;
	    printf("%d was inserted into position %d",newnode->data,position);
	    break;
	}
	index++;
	current = current->next;
    }

    if(index > position) printf("position is out of bounds. Please Try again!");
}

int main() {
    int choice = -1;
    while(choice != 0) {

	printf("\n\nSelect an option to perform: 1- InsertAtBeginning 2- InsertAtEnd 3- InsertAtPosition 4- display 5- DeleteFromBeginning 6- DeleteFromEnd 7-DeleteAtPosition 8-Search 0-QUIT: ");
	scanf("%d",&choice);

        switch(choice) {
	    case 0: printf("Quitting Program...\n"); break;;
	    case 1: insertAtBeginning(getValue()); break;
	    case 2: insertAtEnd(getValue()); break;
	    case 3: insertAtPosition(getValue(),getPosition()); break;
	    case 4: displayList(); break;
	    case 5: deleteFromBeginning(); break;
 	    case 6: deleteFromEnd(); break;
	    case 7: deleteAtPosition(getPosition()); break;
	    case 8: search(getValue()); break;
	    default: printf("Invalid Input\n");
	}
    }

    return 0;
}
