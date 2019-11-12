#include<stdio.h>
#include<stdlib.h>
typedef struct tree{
	int num;
	struct tree *pLeft;
	struct tree *pRight;
}BinaryTree;

//实现树的广度遍历的辅助队列
typedef struct queue{
	BinaryTree *bValue;
	struct queue *pNext;
}MyQueue;
typedef struct {
	int nSize;
	MyQueue *pHead;
	MyQueue *pTail;
}Queue;
//创建一个固定值的二叉树
BinaryTree *CreateTree(){
	BinaryTree* root = (BinaryTree*)malloc(sizeof(BinaryTree));	
	root->num = 1;
	
	root->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->num = 2;
	root->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->pLeft->num = 4;
	root->pLeft->pLeft->pLeft = NULL;
	root->pLeft->pLeft->pRight = NULL;

	root->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->pRight->num = 5;
	root->pLeft->pRight->pLeft = NULL;
	root->pLeft->pRight->pRight = NULL;

	root->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pRight->num = 3;
	root->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pRight->pLeft->num = 6;
	root->pRight->pLeft->pLeft = NULL;
	root->pRight->pLeft->pRight = NULL;

	root->pRight->pRight = NULL;

	return root;
}
	
//初始化
void Q_Init(Queue **pQueue){
	(*pQueue) = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
	(*pQueue)->nSize  = 0;
}

//入队
void Q_Push(Queue *pQueue, BinaryTree *num){
	if(pQueue == NULL)	return;
	//申请节点
	MyQueue *pTemp = NULL;
	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->bValue = num;
	pTemp->pNext = NULL;
	//插入
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
BinaryTree *Q_Pop(Queue *pQueue){
	if(pQueue == NULL || pQueue->nSize == 0){
		return NULL;	
	}
	MyQueue *pDel = NULL;
	BinaryTree *pNum;
	pDel = pQueue->pHead;
	pNum = pDel->bValue;

	pQueue->pHead = pQueue->pHead->pNext;
	free(pDel);
	pDel = NULL;
	pQueue->nSize--;
	if(pQueue->nSize== 0)
		pQueue->pTail = NULL;
	return pNum;

}

//树的层次遍历(树的广度遍历)
void LevelTraversalTree(BinaryTree *pTree){
	if(pTree == NULL) return;
	//初始化队列
	Queue *queue = NULL;
	Q_Init(&queue);
	Q_Push(queue, pTree);
	while(queue->nSize != 0){
		BinaryTree *p = Q_Pop(queue);
		printf("%d\t", p->num);
		
		//左孩子不空 则入队列
		if(p->pLeft != NULL){
			Q_Push(queue,p->pLeft);	
		}

		//右孩子不空 则入队
		if(p->pRight != NULL){
			Q_Push(queue,p->pRight);
		}
		
	}

}
int main(){
	BinaryTree *p = NULL;
	p = CreateTree();
	LevelTraversalTree(p);
	return 0;	
}
