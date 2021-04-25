/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("----------------------[Seojin LEE][2020039034]------------------\n\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));      //헤드노트에 대해 메모리 할당
	(**h).first = NULL; //headnode 초기화 

	return 1;
}

int freeList(headNode* h) {

	listNode* n = h->first;    //헤드 노드가 가리키는 곳= 현재 노드가 가리키는 곳
	listNode* prev = NULL;

	while (n != NULL) { // list의 node들 해제
		prev = n;    // 이전 노드를 n로 변경
		n = n->rlink;    // 다음 노드를 가리키도록 변경
		free(prev);      // 노드를 하나씩 해제
	}

	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* n = (listNode*)malloc(sizeof(listNode));  //새로 삽입할 노드 동적 할당

	n->key = key;
	n->rlink = NULL;
	listNode* node = h->first;

	if (node == NULL) { // 리스트가 NULL이면 맨 앞에 node 삽입

		h->first = n;
	}
	else {
		while (node->rlink != NULL)
		{
			node = node->rlink;    // 리스트 끝까지 포인터 이동
		}
		node->rlink = n; // 맨 뒤에 삽입
		n->llink = node; // llink 연결
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* node = h->first;
	int count = NULL;

	if (h == NULL) {
		printf("Node is not initialized.\n\n");  //초기화된 리스트가 없다면 에러 문구 출력
		return 0;
	}

	if (node == NULL) {
		printf("Linked list is empty!!\n\n");   //초기화된 리스트에 노드가 없으면
		return 0;
	}

	if (node->rlink == NULL) { // 리스트에 node가 하나만 존재하면
		h->first = NULL; // 리스트가 공백
		free(node);
		return 0;
	}
	else {  //노드가 하나 이상 있으면
		while (node->rlink != NULL)
		{     //가장 마지막 노드에 도달할때까지
			node = node->rlink;
			count += 1;
		}

		if (count != 0)
		{
			(node->llink)->rlink = NULL;
		}
		else
		{
			h->first = NULL;
		}
		free(node);
		return 0;
	}
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* n = h->first;

	listNode* next, * prev;
	next, prev = NULL;


	if (h == NULL)
	{
		printf("Head Node is not initialized.\n");
		return 0;
	}
	if (h->first == NULL)
	{
		printf("Linked list is empty!!\n\n");    // 리스트가 비었으면
		return 0;
	}

	while (h->first != NULL) {
		next = prev;						
		prev = n;						

		n = n->rlink;				//다음 노드의 위치 저장
		prev->rlink = next;
		prev->llink = n;
	}

	h->first = prev;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* n = h->first;
	listNode* prev = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)
		h->first = node; // 만약 리스트가 비어있다면 first가 가리키고 있는 노드를 node로


	else {

		if (n->key >= node->key)
		{
			node->rlink = n;
			n->llink = node;
			h->first = node;
		}

		else {

			while (n->key < node->key)
			{

				if (n->rlink == NULL && n->key <= node->key) {
					node->rlink = n->rlink;
					n->rlink = node;
					node->llink = n;

					return 0;
				}
				prev = n;
				n = n->rlink;
			}


			prev->rlink = node;
			node->llink = prev;

			node->rlink = n;
			n->llink = node;
		}
	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* n;
	n = h->first;
	listNode* prev = NULL;


	if (h->first == NULL)
		printf("List is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력



	else {
		while (n->rlink != NULL)
		{
			if (n->key == key)
			{

				h->first = n->rlink;
				free(n);
			}
		}

		if (n->key != key)
		{
			while (n->key != key) {
				prev = n;          //키값이 같지 않으면 이전노드를 현 위치로 설정
				n = n->rlink;

				if (n == NULL)
				{
					printf("키를 찾는데 실패하였습니다.!!\n\n"); //  
					return 0;
				}

			}

			prev->rlink = n->rlink;
			n->rlink->llink = prev;
			free(n);
		}
	}
	return 1;
}
