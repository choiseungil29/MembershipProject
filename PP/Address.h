//
//  Address.h
//  PP
//
//  Created by Pooh on 2014. 7. 25..
//  Copyright (c) 2014년 Pooh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct address {
	int id;
	char name[100];
	char phone[100];
	char home[100];
} Address;

typedef struct node {
	struct address* value;
	struct node *next;
} Node;

typedef struct list {
	int length;
	struct node *head;
} List;

typedef enum {false, true} bool;

List* createList();
void insert(List**, Address *);
void search(List*);
List* findByName(List *list, char* name);
List* findByPhone(List *list, char* phone);
List* findByHome(List *list, char *home);
void find(List*(*param)(List*,char*), List*, char*);
