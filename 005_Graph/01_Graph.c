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

//定义的一个深度遍历的方法
void MyDFS(Graph *pGraph, int num, int* pMark){
	printf("%d\t", num);
	pMark[num - 1] = 1;
	int i;
	for(i = 0; i < pGraph->nVertex; i++){
		if(pGraph->pMatrix[(num - 1) * pGraph->nVertex + i] == 1 && pMark[i] == 0){
			MyDFS(pGraph, i + 1, pMark);
		}	
	}
}

//深度遍历
void DFS(Graph *pGraph, int num){
	if(pGraph == NULL)return;
	int *pMark = NULL;
	pMark = (int*)malloc(sizeof(int) * (pGraph->nVertex));
	memset(pMark, 0, sizeof(int) * (pGraph->nVertex));
	MyDFS(pGraph, num, pMark);
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
	DFS(p, 5);
	return 0;	
}
