//
//  Address.c
//  PP
//
//  Created by Pooh on 2014. 7. 25..
//  Copyright (c) 2014년 Pooh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Address.h"

List* createList() {
    List* list = (List*)malloc(sizeof(List*));
	list->head = NULL;
	list->length = 0;
    return list;
}

Address* create(char* name, char* phone, char* home) {
	Address* value = (Address*)malloc(sizeof(Address*));
    
	value->id = 132123;
	strcpy(value->name, name);
	strcpy(value->phone, phone);
	strcpy(value->home, home);
    
	return value;
}

void insert(List **list, Address *address) {
	Node *temp = NULL;
	Node *node = (Node*)malloc(sizeof(Node*));
	node->value = address;
    
	if((*list)->head == NULL) {
        node->value->id = 10000;
		(*list)->head = node;
		(*list)->length = 1;
	} else {
		temp = (*list)->head;
		while(temp->next != NULL) {
			temp = temp->next;
		}
        node->value->id = temp->value->id+1;
		temp->next = node;
        temp->next->next = NULL;
		(*list)->length++;
        printf("length : %d\n", (*list)->length);
	}
}

void search(List *list) {
	Node *temp = list->head;
    
    int count = 0;
	while(temp != NULL) {
		Address* value = temp->value;
        printf("count : %d\n", count+1);
        printf("%d\t%s\t%s\t%s\n", value->id, value->name, value->phone, value->home);
        printf("\n");
        temp = temp->next;
        count++;
	}
}

List* findByName(List *list, char* name) {
    Node *temp = list->head;
    List* ret_list = createList();
    
	while(temp != NULL) {
		Address* value = temp->value;
        if(strcmp(value->name, name) == 0) {
            printf("찾았당!\n");
            insert(&ret_list, value);
        }
        temp = temp->next;
	}
    
    if(ret_list->length == 0) {
        return NULL;
    }
    
    return ret_list;
}

List* findByPhone(List *list, char *phone) {
    Node *temp = list->head;
    List *ret_list = createList();
    
    while(temp != NULL) {
        Address* value = temp->value;
        if(strcmp(value->phone, phone) == 0) {
            printf("찾았당!\n");
            insert(&ret_list, value);
        }
        temp = temp->next;
    }
    
    if(ret_list->length == 0) {
        return NULL;
    }
    
    return ret_list;
}

List* findByHome(List *list, char *home) {
    Node *temp = list->head;
    List *ret_list = createList();
    
    while(temp != NULL) {
        Address* value = temp->value;
        if(strcmp(value->home, home) == 0) {
            printf("찾았당!\n");
            insert(&ret_list, value);
        }
        temp = temp->next;
    }
    
    if(ret_list->length == 0) {
        return NULL;
    }
    
    return ret_list;
}

void find(List*(*param)(List *, char *), List *list, char *value) {
    List* items = param(list, value);
    if(items == NULL) {
        printf("일치하는 결과를 찾지 못했습니다.\n");
        backToMainScene();
    } else {
        printf("일치하는 결과 목록입니다.\n");
        search(items);
        backToMainScene();
    }
}



