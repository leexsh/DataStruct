#include<stdio.h>
#include<stdlib.h>
typedef struct tree{
	int num;
	struct tree *pLeft;
	struct tree *pRight;
}BinaryTree;

//实现树的非递归遍历的辅助栈
typedef struct stack{
	BinaryTree *bValue;
	struct stack *pNext;
}MyStack;

typedef struct {
	int nSize;
	MyStack *pTop;
}Stack;


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
void S_Init(Stack **pStack){
	(*pStack) = (Stack*)malloc(sizeof(Stack));
	(*pStack)->pTop = NULL;
	(*pStack)->nSize  = 0;
}

//入栈
void S_Push(Stack *pStack, BinaryTree *num){
	if(pStack == NULL)	return;
	//申请节点
	MyStack *pTemp = NULL;
	pTemp = (MyStack*)malloc(sizeof(MyStack));
	pTemp->bValue = num;
	pTemp->pNext = pStack->pTop;
	pStack->nSize++;
	pStack->pTop = pTemp;
}


//出栈
BinaryTree *S_Pop(Stack *pStack){
	if(pStack == NULL || pStack->nSize == 0){
		return NULL;	
	}
	MyStack *pDel = NULL;
	pDel = pStack->pTop;
	BinaryTree *pNum;
	pNum = pDel->bValue;
	pStack->pTop = pStack->pTop->pNext;
	pStack->nSize--;
	free(pDel);
	pDel = NULL;
	return pNum;
}
		
//二叉树的非递归前序遍历
void ProOrderNoDiGui(BinaryTree *pTree){
	if(pTree == NULL) return;
	//创造一个栈
	Stack *pStack;
	S_Init(&pStack);

	while(1){
		//节点非空 打印 向左走
		while(pTree != NULL)
		{
			printf("%d\t", pTree->num);
			S_Push(pStack, pTree);
			pTree = pTree->pLeft;
		}
		//弹出
		pTree = S_Pop(pStack);
		if(pTree == NULL)
			break;
		//右
		pTree = pTree->pRight;
	}
}

//二叉树的中序非递归遍历
void InOrderUnDiGui(BinaryTree *pTree){
	if(pTree == NULL)
		return;
	Stack *pStack;
	S_Init(&pStack);
	while(1){
		//节点非空 向左走
		while(pTree){
			S_Push(pStack, pTree);
			pTree = pTree->pLeft;		
		}
		//弹出
		pTree = S_Pop(pStack);
		if(pTree == NULL)
		{
			break;
		}
		printf("%d\t", pTree->num);

		pTree = pTree->pRight;
	}
}

//二叉树的非递归后序遍历
void  LastOrderUnDiGui(BinaryTree *pTree){
	if(pTree == NULL)
		return;
	Stack *pStack;
	S_Init(&pStack);
	BinaryTree *pTemp = NULL;
	while(1){
		while(pTree){
			S_Push(pStack,pTree);
			pTree = pTree->pLeft;
		}
		if(pStack->pTop->bValue->pRight == pTemp || pStack->pTop->bValue->pRight == NULL){
			pTemp = S_Pop(pStack);
			printf("%d\t", pTemp->num);
			if(pStack->pTop == NULL)
				break;
		}
		else{
			pTree = pStack->pTop->bValue->pRight;
		}
				
	}
	
}

int main(){
	BinaryTree *p = NULL;
	p = CreateTree();
	
	ProOrderNoDiGui(p);
	printf("\n");
	InOrderUnDiGui(p);
	printf("\n");
	LastOrderUnDiGui(p);
	return 0;	
}
