#include<stdio.h>
#include<stdlib.h>
typedef struct queue{
	int m_nNum;
	struct queue *pNext;	
}MyQueue;

typedef struct {
	int nSize;
	MyQueue *pHead;
	MyQueue *pTail;
}Queue;

//两个队列实现栈的结构体
typedef struct stack{
	int nSize;
	Queue *queue1;
	Queue *queue2;
}Stack;


//初始化
void Init(Queue **pQueue){
	(*pQueue) = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
	(*pQueue)->nSize = 0;
}
//入队
void Push(Queue *pQueue,int num){
	if(pQueue == NULL) return;
	MyQueue *pTemp = NULL;
	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->m_nNum = num;
	pTemp->pNext = NULL;
	if(pQueue->pHead == NULL){
		pQueue->pHead = pTemp;	
	}
	else{
		pQueue->pTail->pNext = pTemp;	
	}
	pQueue->pTail = pTemp;
	pQueue->nSize++;
}

//出队
int Pop(Queue *pQueue){
	if(pQueue == NULL || pQueue->nSize == 0)
		return -1;
	MyQueue *pDel = NULL;
	pDel = pQueue->pHead;
	int num = pDel->m_nNum;
	pQueue->pHead = pQueue->pHead->pNext;

	free(pDel);
	pDel = NULL;
	pQueue->nSize--;
	if(pQueue->pHead == NULL){
		pQueue->pTail = NULL;
	}

	return num;

}
//判断队是否为空
int IsEmpty(Queue *pQueue){
	return pQueue->nSize == 0 ? 1 : 0;
}

//两个队列实现的栈的初始化
void S_Init(Stack **pStack){
	(*pStack) = (Stack*)malloc(sizeof(Stack));
	(*pStack)->nSize = 0;
	Init(&((*pStack)->queue1));
	Init(&((*pStack)->queue2));
	
}
//两个对列实现栈的入栈
void S_Push(Stack *pStack, int num){
	if(pStack == NULL || pStack->queue1 == NULL || pStack->queue2 == NULL)
		return;
	//哪个队列不空 入哪个
	if(pStack->queue1->nSize != 0){
		Push(pStack->queue1, num);	
	}else{
		Push(pStack->queue2, num);
	}
	pStack->nSize++;
}
//两个队列实现栈的出栈
int S_Pop(Stack *pStack){
	if(pStack == NULL || pStack->queue1 == NULL || pStack->queue2 == NULL || pStack->nSize == 0)
		return -1;
	int num;
	if(pStack->queue1->nSize != 0){
		while(pStack->queue1->nSize > 1){
			Push(pStack->queue2, Pop(pStack->queue1));
		}
		num = Pop(pStack->queue1);
	}
	else{
		while(pStack->queue2->nSize > 1){
			Push(pStack->queue1, Pop(pStack->queue2));
		}	
		num = Pop(pStack->queue2);
	}

	pStack->nSize--;
	return num;
}
int main(){
	Queue *p;
	Init(&p);
	Push(p, 1);
	Push(p, 2);
	Push(p, 3);
	Push(p, 4);
	printf("%d\n", Pop(p));
	printf("%d\n", Pop(p));
	printf("%d\n", Pop(p));
	printf("%d\n", Pop(p));
	printf("-------------------\n");
	Stack *pStack;
	S_Init(&pStack);
	S_Push(pStack, 1);
	S_Push(pStack, 2);
	S_Push(pStack, 3);
	S_Push(pStack, 4);
	printf("%d\n", S_Pop(pStack));
	printf("%d\n", S_Pop(pStack));
	printf("%d\n", S_Pop(pStack));
	printf("%d\n", S_Pop(pStack));
	return 0;	
}
