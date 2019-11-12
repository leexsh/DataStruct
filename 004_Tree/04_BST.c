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
//查找某一个节点
void SearchNode(BST *pTree, int num, BST **pDel, BST **pFather){

	//pFather是pDel的父节点
	while(pTree){
		if(pTree->num > num){
			*pFather = pTree;
			pTree = pTree->pLeft;
		}
		else if(pTree->num < num){
			*pFather = pTree;
			pTree = pTree->pRight;
		}
		else{
			*pDel = pTree;
			return;
		}
		
	}
	//pDel是根节点或者没有找到
	*pFather = NULL;
	
}

//在二叉搜索树中删除一个节点
void DelNodeInBST(BST **pTree, int nDel){
	if(*pTree == NULL)return;

	//查找
	BST *pDel = NULL;
	BST *pFather = NULL;
	SearchNode(*pTree, nDel, &pDel, &pFather);
	
	//没找到
	if(pDel == NULL)
		return;
	
	//标记的指针
	BST *pMark = NULL;
	//删除的节点右两个孩子
	if(pDel->pLeft != NULL && pDel->pRight != NULL){
		//标记指针指向要删除的节点
		pMark = pDel;
		//pDel和pFather分别向下一个 要找删除节点左的最右节点 或者右的最左节点
		pFather = pDel;
		pDel = pDel->pLeft;
		//找左的最右节点
		while(pDel->pRight != NULL){
			pFather = pDel;
			pDel = pDel->pRight;
		}
		//将左的最右节点的值赋给要删除的节点
		pMark->num = pDel->num;
	}
	// 删除的节点只有一个孩子或者没有孩子
	//删除的节点是根节点的情况
	if(pFather == NULL){
		(*pTree) = pDel->pLeft ? pDel->pLeft : pDel->pRight;	
	}

	//如果删除的节点是父亲节点的左孩子 要把删除节点的孩子跟父亲节点连接
	if(pDel == pFather->pLeft){
		pFather->pLeft = pDel->pLeft ? pDel->pLeft : pDel->pRight;	
	}
	//如果删除的节点是父亲节点的右孩子 也要连接
	if(pDel == pFather->pRight){
		pFather->pRight = pDel->pLeft ? pDel->pLeft :pDel->pRight;	
	}

	free(pDel);
	pDel = NULL;

	
}
	

//中序遍历 二叉搜索树的中序遍历 是从小到大递增的
void Inorder(BST *pTree){
	if(pTree == NULL)return ;

	Inorder(pTree->pLeft);
	printf("%d\t", pTree->num);
	Inorder(pTree->pRight);
}
int main(){
	
	int arr[] = {10,2,1,99,3,16,20,18};
	BST *p = NULL;
	p = CreateBST(arr, sizeof(arr)/ sizeof(arr[0]));
	Inorder(p);
	printf("\n");
	DelNodeInBST(&p, 16);
	Inorder(p);
	printf("\n");
	return 0;
}
