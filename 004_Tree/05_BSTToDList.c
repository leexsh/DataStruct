#include<stdio.h>
#include<stdlib.h>
typedef struct tree{
	int num;
	struct tree *pLeft;
	struct tree *pRight;
}BST;


//向BST中添加节点
void AddNode(BST **pTree, int num){
	//创建一个节点
	BST *pTemp = (BST*)malloc(sizeof(BST));
	pTemp->num = num;
	pTemp->pRight = NULL;
	pTemp->pLeft = NULL;
	
	if((*pTree) == NULL){
		(*pTree) = pTemp;
		return;
	}

	BST *p = (*pTree);
	while(p){
		if(p->num > num){
			if(p->pLeft == NULL){
				p->pLeft = pTemp;
				return;
			}	
			p = p->pLeft;
		}
		else if(p->num < num){
			if(p->pRight == NULL){
				p->pRight = pTemp;
				return;
			}	
			p = p->pRight;
		}
		else{
			printf("Error\n");
			free(pTemp);
			pTemp = NULL;
			return;
		}
	
	}
}

//构造一个二叉搜索树
BST *CreateBST(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)return NULL;
	int i;
	BST *pTree = NULL;
	for(i = 0; i < nLen; i++){
		AddNode(&pTree, arr[i]);	
		
	}
	return pTree;
}

//将二叉搜索树变为双向链表
void BSTToDList(BST *pTree, BST **pHead, BST **pTail){
	if(pTree == NULL) return;
	//左
	BSTToDList(pTree->pLeft, pHead, pTail);
	//尾添加
	if((*pHead) == NULL){
		*pHead = pTree;	
	}else{
		(*pTail)->pRight = pTree;
		pTree->pLeft = *pTail;

	}
	(*pTail) = pTree;
	//右
	BSTToDList(pTree->pRight, pHead, pTail);

}


//中序遍历 二叉搜索树的中序遍历 是从小到大递增的
void Inorder(BST *pTree){
	if(pTree == NULL)return ;

	Inorder(pTree->pLeft);
	printf("%d\t", pTree->num);
	Inorder(pTree->pRight);
}

void PrintList(BST *pHead){
	while(pHead){
		printf("%d\t", pHead->num);
		pHead = pHead->pRight;
	}
}
int main(){
	
	int arr[] = {10,2,1,99,3,16,20,18};
	BST *p = NULL;
	p = CreateBST(arr, sizeof(arr)/ sizeof(arr[0]));
	Inorder(p);
	printf("\n");
	BST *pHead = NULL;
	BST *pTail = NULL;
	BSTToDList(p ,&pHead, &pTail);
	//PrintList(pHead);
	while(pHead){
		printf("%d\t", pHead->num);
		pHead = pHead->pRight;
	}
	printf("\n");
	return 0;
}
