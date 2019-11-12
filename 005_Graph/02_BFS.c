#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct graph{
	int nVertex;
	int nEdge;
	int *pMatrix;
	
}Graph;
Graph *CreateGraph(){
	int nV, nE;
	printf("输入顶点和边的数目\n");
	scanf("%d%d", &nV, &nE);
	Graph *pGraph = NULL;
	pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->nVertex = nV;
	pGraph->nEdge = nE;

	//申请一个临接矩阵
	pGraph->pMatrix = (int*)malloc(sizeof(int) * nV * nV);
	//内存置0
	memset(pGraph->pMatrix, 0, sizeof(int) * nV * nV);
	int i,v1,v2;

	for(i = 0; i < nE; i++){
		printf("请输入v1,v2 表示v1v2之间有一条变\n");
		scanf("%d%d",&v1, &v2);
		if(v1 >= 1 && v1 <= nV && v2 >= 1 && v2 <= nV && pGraph->pMatrix[(v1 - 1) * nV + (v2 - 1)] == 0){
			pGraph->pMatrix[(v1 - 1) * nV + (v2 - 1)] = 1;
			pGraph->pMatrix[(v2 - 1)* nV + (v1 - 1)] = 1;
		}else{
			i--;	
		}
	}
	return pGraph;
}


typedef struct queue{
	int m_nNum;
	struct queue *pNext;	
}MyQueue;

typedef struct {
	int nSize;
	MyQueue *pHead;
	MyQueue *pTail;
}Queue;


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

//广度遍历
void BFS(Graph *pGraph, int num){
	if(pGraph == NULL)return;
	Queue *q = NULL;
	Init(&q);
	int *pMark = NULL;
	pMark = (int *)malloc(sizeof(int) * pGraph->nVertex);
	memset(pMark, 0, sizeof(int)*pGraph->nVertex);
	pMark[num - 1] = 1;

	Push(q, num);
	int i;
	while(q->nSize !=  0){
		num = Pop(q);
		printf("%d\t",num );
		for(i = 0; i < pGraph->nVertex; i++){
			if(pMark[i] == 0 && pGraph->pMatrix[(num - 1) * pGraph->nVertex + i] == 1){
				Push(q, i+1);	
				pMark[i] = 1;

			}	
		}
		
	}
	
}
int main(){
	Graph *p = NULL;
	p = CreateGraph();
	int i;
	for(i = 0; i < p->nVertex * p->nVertex; i++){
		if(i % p->nVertex == 0 && i != 0){
			printf("\n");	
		}	
		printf("%d\t", p->pMatrix[i]);
	}

	printf("------------------\n");
	printf("\n");
	BFS(p, 5);
	return 0;	
}
