#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.h"

void loop();

Address* create(char* name, char* phone, char* home);

int main() {
	printf("log\n");
	List* list = NULL;

	init(&list);

	Address* value = create("asd", "asd", "asd");
	insert(&list, value);

	loop();

	return 0;
}

Address* create(char* name, char* phone, char* home) {
	Address* value = (Address*)malloc(sizeof(Address*));
	value->id = 132123;
	value->name = (char*)malloc(strlen(name) + 1);
	strcpy(value->name, name);

	value->phone = (char*)malloc(strlen(phone) + 1);
	strcpy(value->phone, phone);

	value->home = (char*)malloc(strlen(home) + 1);
	strcpy(value->phone, phone);

	return value;
}

void loop() {

}

void init(List **list) {
	list = (List**)malloc(sizeof(List**));
	(*list) = (List*)malloc(sizeof(List*));
	(*list)->head = NULL;
	(*list)->length = 0;
}

void insert(List **list, Address *address) {
	Node *temp = NULL;
	Node *node = (Node*)malloc(sizeof(Node*));
	node->value = address;

	if((*list)->head == NULL) {
		(*list)->head = node;
		(*list)->length = 1;
	} else {
		temp = (*list)->head;
		while(temp != NULL) {
			temp = temp->next;
		}
		temp = node;
		(*list)->length++;
	}
}

void search(List **list) {
	Node *temp = (*list)->head;

	while(temp != NULL) {
		Address* value = temp->value;
		printf("%d\n", value->id);
		printf("%s\n", value->name);
		printf("%s\n", value->phone);
		printf("%s\n", value->home);
	}
}









