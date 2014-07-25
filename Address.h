#include <stdio.h>
#include <stdlib.h>

typedef struct address {
	int id;
	char* name;
	char* phone;
	char* home;
} Address;

typedef struct node {
	struct address* value;
	struct node *next;
} Node;

typedef struct list {
	int length;
	node *head;
} List;

void init(List**);
void insert(List**, Address *);
void search(List**);