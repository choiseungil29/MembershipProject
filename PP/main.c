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

bool isCorrectName(char*);
bool isCorrectPhone(char*);

void createFile();
void saveFile();

void inputName(char*);
void inputPhone(char*);
void inputHome(char*);

Address* create(char*, char*, char*);

List* list = NULL;

int main() {
    list = createList();
    createFile();
	loop();
    
	return 0;
}

void createFile() {
    FILE* fp = fopen("data.txt", "r");
    if(fp == false) {
        return;
    }
    while(feof(fp) == 0) {
        int id = 0;
        char name[100];
        char phone[100];
        char home[100];
        
        fscanf(fp, "%d", &id);
        fscanf(fp, "\t");
        fscanf(fp, "%s", name);
        fscanf(fp, "\t");
        fscanf(fp, "%s", phone);
        fscanf(fp, "\t");
        //fscanf(fp, "%s", home);
        fgets(home, sizeof(home), fp);
        fscanf(fp, "\n");
        Address* value = create(name, phone, home);
        value->id = id;
        insert(&list, value);
    } // 최초 초기화 문제 해결해야함.
}

void saveFile() {
    FILE* fp = fopen("data.txt", "w");
    Node* temp = list->head;
    while(temp != NULL) {
        Address* value = temp->value;
        fprintf(fp, "%d\t%s\t%s\t%s\n", value->id, value->name, value->phone, value->home);
        temp = temp->next;
    }
    fclose(fp);
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
    printf("6. 저장하고 종료.\n");
    printf("7. 저장안하고 종료.\n");
    
    char letter = '0';
    scanf("%c", &letter);
    getchar();
    
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
    } else if(letter == '6') {
        saveFile();
        exit(0);
    } else if(letter == '7') {
        exit(0);
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
    
    do {
        inputName(name);
    } while (!isCorrectName(name));
    
    do {
        inputPhone(phone);
    } while(!isCorrectPhone(phone));
    
    inputHome(home);
    
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
        inputName(param);
        find(&findByName, list, param);
    } else if(letter == '2') { // 전화번호
        inputPhone(param);
        find(&findByPhone, list, param);
    } else if(letter == '3') { // 주소
        inputHome(param);
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
        inputName(param);
        items = findByName(list, param);
    } else if(letter == '2') {
        inputPhone(param);
        items = findByPhone(list, param);
    } else if(letter == '3') {
        inputHome(param);
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
                        printf("작업이 마무리되었습니다.\n");
                        backToMainScene();
                        return;
                    } else {
                        if(temp->next != NULL) {
                            prevNode->next = temp->next;
                            printf("작업이 마무리되었습니다.\n");
                            backToMainScene();
                            return;
                        } else {
                            prevNode->next = NULL;
                            printf("작업이 마무리되었습니다.\n");
                            backToMainScene();
                            return;
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
        inputName(param);
        items = findByName(list, param);
    } else if(letter == '2') {
        inputPhone(param);
        items = findByPhone(list, param);
    } else if(letter == '3') {
        inputHome(param);
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
                        if(!isCorrectName(newParam)) {
                            printf("잘못된 입력입니다. 한글만 입력해주세요.\n");
                            continue;
                        }
                        strcpy(value->name, newParam);
                    } else if(result == '2') {
                        printf("새로운 전화번호를 입력해주세요.\n");
                        if(!isCorrectPhone(newParam)) {
                            printf("잘못된 입력입니다. xxx-xxxx-xxxx의 포맷으로 입력해주세요.\n");
                            continue;
                        }
                        scanf("%s", newParam);
                        strcpy(value->name, newParam);
                    } else if(result == '3') {
                        printf("새로운 주소를 입력해주세요.\n");
                        scanf("%s", newParam);
                        strcpy(value->name, newParam);
                    } else {
                        printf("잘못된 입력입니다. 1~3 중 선택해주세요.\n");
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
    printf("엔터를 입력하시면 처음 화면으로 돌아갑니다.\n");
    getchar();
    fflush(stdin);
    scene = &mainScene;
}

bool isCorrectName(char* name) {
    int length = (int)strlen(name);
    int i=0;
    bool check = true;
    
    for(i=0; i<length; i++) {
        if((name[i] & 0x80) != 0x80) {
            check = false;
        }
    }
    
    return check;
}

bool isCorrectPhone(char* phone) {
    int length = (int)strlen(phone);
    int i=0;
    
    if(length != 13) { // 길이제한 어긋남
        return false;
    }
    
    for(i=0; i<length; i++) {
        if(!(phone[i] >= '0' && phone[i] <= '9')) {
            if(!((i == 3 || i == 8) && (phone[i] == '-'))) {
                return false;
            }
        }
    }
    
    return true;
}

void inputName(char* str) {
    printf("이름을 입력해주세요 : ");
    scanf("%99s", str);
    getchar();
}

void inputPhone(char* str) {
    printf("전화번호를 입력해주세요 : ");
    scanf("%99s", str);
    getchar();
}

void inputHome(char* str) {
    printf("주소를 입력해주세요 : ");
    scanf("%99[^\n]s", str);
    //scanf("%99s", str);
    getchar();
}





