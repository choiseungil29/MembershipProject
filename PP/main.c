//
//  main.c
//  PP
//
//  Created by Pooh on 2014. 7. 25..
//  Copyright (c) 2014년 Pooh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.h"

void loop();
void (*scene)();
void mainScene();
void browseScene();
void addScene();
void findScene();
void removeScene();
void amendScene();

void testCase();

void backToMainScene();

Address* create(char*, char*, char*);

List* list = NULL;

int main() {
    list = createList();
    
	loop();
    
	return 0;
}

void loop() {
    printf("시작합니다.\n");
    scene = &mainScene;
    while(1) {
        scene();
    }
}

void mainScene() {
    printf("1. 회원 전체보기.\n");
    printf("2. 회원 추가하기.\n");
    printf("3. 회원 검색하기.\n");
    printf("4. 회원 삭제하기.\n");
    printf("5. 회원 수정하기.\n");
    
    char letter = '0';
    scanf("%c", &letter);
    
    if(letter == '1') {
        scene = &browseScene;
    } else if(letter == '2') {
        scene = &addScene;
    } else if(letter == '3') {
        scene = &findScene;
    } else if(letter == '4') {
        scene = &removeScene;
    } else if(letter == '5') {
        scene = &amendScene;
    }
    
}

void browseScene() {
    search(list);
    backToMainScene();
}

void addScene() {
    char name[100];
    char phone[100];
    char home[100];
    
    printf("이름을 입력해주세요 : ");
    scanf("%s", name);
    
    printf("전화번호를 입력해주세요 : ");
    scanf("%s", phone);
    
    printf("주소를 입력해주세요 : ");
    scanf("%s", home);
    
    insert(&list, create(name, phone, home));
    backToMainScene();
}

void findScene() {
    printf("회원을 검색합니다.\n");
    printf("1. 이름으로 검색.\n");
    printf("2. 전화번호로 검색.\n");
    printf("3. 주소로 검색.\n");
    
    int letter = getchar();
    getchar();
    
    char param[100];
    
    if(letter == '1') { // 이름
        printf("이름을 입력해주세요 : ");
        scanf("%s", param);
        find(&findByName, list, param);
    } else if(letter == '2') { // 전화번호
        printf("전화번호를 입력해주세요 : ");
        scanf("%s", param);
        find(&findByPhone, list, param);
    } else if(letter == '3') { // 주소
        printf("주소를 입력해주세요 : ");
        scanf("%s", param);
        find(&findByHome, list, param);
    }
}

void removeScene() {
    printf("회원을 삭제합니다.\n");
    printf("1. 이름으로 검색.\n");
    printf("2. 전화번호로 검색.\n");
    printf("3. 주소로 검색.\n");
    
    int letter = getchar();
    getchar();
    
    char param[100];
    
    List* items = NULL;
    
    if(letter == '1') {
        printf("이름을 입력해주세요 : ");
        scanf("%s", param);
        items = findByName(list, param);
    } else if(letter == '2') {
        printf("전화번호를 입력해주세요 : ");
        scanf("%s", param);
        items = findByPhone(list, param);
    } else if(letter == '3') {
        printf("주소를 입력해주세요 : ");
        scanf("%s", param);
        items = findByHome(list, param);
    }
    
    if(items == NULL) {
        printf("일치하는 결과를 찾지 못했습니다.\n");
        backToMainScene();
    } else {
        printf("일치하는 결과 목록입니다.\n");
        
        Node *prevNode = NULL;
        Node *temp = list->head;
        while(temp != NULL) {
            Address* value = temp->value;
            printf("name : %s\n", value->name);
            printf("phone : %s\n", value->phone);
            printf("home : %s\n", value->home);
            
            Node* targetNode = items->head;
            while(targetNode != NULL) {
                
                if(value->id == targetNode->value->id) {
                    printf("삭제하시겠습니까? (y/n) : ");
                    int result = getchar();
                    getchar();
                    if(!(result == 'y' || result == 'Y')) {
                        targetNode = targetNode->next;
                        continue;
                    }
                    if(prevNode == NULL) {
                        list->head = temp->next;
                    } else {
                        if(temp->next != NULL) {
                            prevNode->next = temp->next;
                        } else {
                            prevNode->next = NULL;
                        }
                    }
                }
                targetNode = targetNode->next;
            }
            
            prevNode = temp;
            temp = temp->next;
        }
    }
    
    printf("작업이 마무리되었습니다.\n");
    backToMainScene();
}

void amendScene() {
    printf("회원을 수정합니다.\n");
    printf("1. 이름으로 검색.\n");
    printf("2. 전화번호로 검색.\n");
    printf("3. 주소로 검색.\n");
    
    int letter = getchar();
    getchar();
    
    char param[100];
    
    List* items = NULL;
    
    if(letter == '1') {
        printf("이름을 입력해주세요 : ");
        scanf("%s", param);
        items = findByName(list, param);
    } else if(letter == '2') {
        printf("전화번호를 입력해주세요 : ");
        scanf("%s", param);
        items = findByPhone(list, param);
    } else if(letter == '3') {
        printf("주소를 입력해주세요 : ");
        scanf("%s", param);
        items = findByHome(list, param);
    }
    
    if(items == NULL) {
        printf("일치하는 결과를 찾지 못했습니다.\n");
        backToMainScene();
    } else {
        printf("일치하는 결과 목록입니다.\n");
        
        Node *prevNode = NULL;
        Node *temp = list->head;
        while(temp != NULL) {
            Address* value = temp->value;
            
            Node* targetNode = items->head;
            while(targetNode != NULL) {
                
                if(value->id == targetNode->value->id) {
                    
                    printf("회원 정보\n");
                    printf("name : %s\n", value->name);
                    printf("phone : %s\n", value->phone);
                    printf("home : %s\n", value->home);
                    printf("\n");
                    printf("어떤 데이터를 수정하시겠습니까?\n");
                    printf("1. 이름\n");
                    printf("2. 전화번호\n");
                    printf("3. 주소\n");
                    char result = '0';
                    scanf("%c", &result);
                    
                    char newParam[100];
                    if(result == '1') {
                        printf("새로운 이름을 입력해주세요.\n");
                        scanf("%s", newParam);
                        //strcpy(targetNode->value->name, newParam);
                        strcpy(value->name, newParam);
                    } else if(result == '2') {
                        printf("새로운 전화번호를 입력해주세요.\n");
                        scanf("%s", newParam);
                        strcpy(value->name, newParam);
                    } else if(result == '3') {
                        printf("새로운 주소를 입력해주세요.\n");
                        scanf("%s", newParam);
                        strcpy(value->name, newParam);
                    } else {
                        continue;
                    }
                }
                targetNode = targetNode->next;
            }
            
            prevNode = temp;
            temp = temp->next;
        }
    }
    
    printf("작업이 마무리되었습니다.\n");
    backToMainScene();
}

void backToMainScene() {
    printf("아무 키나 입력하시면 처음 화면으로 돌아갑니다.\n");
    getchar();
    getchar();
    scene = &mainScene;
}



