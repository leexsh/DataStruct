#include<stdio.h>
#include<stdlib.h>
//栈的结构体
typedef struct stack{
	int num;
	struct stack *pNext;
}MyStack;
//对栈进行封装
typedef struct vector{
	MyStack *pTop;
	int nCount;
}Stack;
//两个栈实现队列的结构体
typedef struct queue{
	Stack *stack1;
	Stack *stack2;
	 int nSize;
}Queue;

//初始化
void Init(Stack **pStack){
	*pStack = (Stack*)malloc(sizeof(Stack));
	(*pStack)->pTop = NULL;
	(*pStack)->nCount = 0;
}
//进栈
void Push(Stack *pStack, int num){
	if(pStack == NULL){
		printf("栈不存在\n");
		return ;
	}
	MyStack *pTemp = NULL;
	pTemp = (MyStack*)malloc(sizeof(MyStack));
	pTemp->num = num;
	pTemp->pNext = pStack->pTop;
	pStack->nCount++;
	pStack->pTop = pTemp;
}
//出栈
int Pop(Stack *pStack){
	if(pStack == NULL || pStack->nCount == 0) return -1;
	MyStack *pDel = NULL;
	pDel = pStack->pTop;
	int num;
	num = pDel->num;

	pStack->pTop = pStack->pTop->pNext;
	pStack->nCount--;
	free(pDel);
	pDel = NULL;
	return num;
}
//clear 清空栈
void Clear(Stack *pStack){
	if(pStack == NULL) return;
	while(pStack->nCount != 0){
		Pop(pStack);
		pStack->nCount--;
	}
}
//销毁栈
void Distory(Stack **pStack){
	Clear(*pStack);
	free(*pStack);
	*pStack = NULL;
}
//获取栈中元素个数
int GetCount(Stack *pStack){
	return pStack->nCount;
}
//获取栈顶元素
MyStack* GetTop(Stack *pStack){

	return pStack->pTop;

}
//判断栈是否为空
int IsEmpty(Stack *pStack){
	return pStack->nCount == 0 ? 1:0;
}

// 两个栈实现队列的初始化
void Q_Init(Queue **pQueue){
	(*pQueue) = (Queue*)malloc(sizeof(Queue));
	Init(&((*pQueue)->stack1));
	Init(&((*pQueue)->stack2));
	(*pQueue)->nSize = 0;
}

//两个栈实现队列的入队
void Q_Push(Queue *pQueue, int num){
	if(pQueue == NULL || pQueue->stack1 == NULL || pQueue->stack2 == NULL)
		return ;
	//如果 s2中有元素 先把s2的元素放入是s1中  再把进来的元素放入 s1中
	while(!IsEmpty(pQueue->stack2)){
		Push(pQueue->stack1, Pop(pQueue->stack2));	
	}
	Push(pQueue->stack1, num);
	pQueue->nSize++;
	
}
//两个栈实现队列的出队
int Q_Pop(Queue *pQueue){
	if(pQueue == NULL || pQueue->stack2 == NULL || pQueue->stack1 == NULL || pQueue->nSize == 0)
		return -1;
	//把有元素的栈全部出去 放入s2 再从s2中拿出栈顶元素
	while(!IsEmpty(pQueue->stack1)){
		Push(pQueue->stack2, Pop(pQueue->stack1));	
	}

	int num = Pop(pQueue->stack2);
	pQueue->nSize--;
	return num;
}


int main(){
	Stack *pStack = NULL;
	Init(&pStack);
	Push(pStack,1);
	Push(pStack, 2);
	Push(pStack,3);
	printf("%d\n ", Pop(pStack));
	printf("\n");
	printf("-----------------\n");
	Queue *pQueue;
	Q_Init(&pQueue);
	Q_Push(pQueue, 1);
	Q_Push(pQueue, 2);
	Q_Push(pQueue, 3);
	Q_Push(pQueue, 4);
	printf("%d\n", Q_Pop(pQueue));
	printf("%d\n", Q_Pop(pQueue));
	printf("%d\n", Q_Pop(pQueue));
	printf("%d\n", Q_Pop(pQueue));
	Distory(&pStack);
	return 0;	
}
