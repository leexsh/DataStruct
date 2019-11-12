#include<stdio.h>
#include<stdlib.h>
typedef struct tree{
	int num;
	struct tree *pLeft;
	struct tree *pRight;
	struct tree *pFather;
}BinaryTree;

//创建一个固定值的二叉树
BinaryTree *CreateTree(){
	BinaryTree* root = (BinaryTree*)malloc(sizeof(BinaryTree));	
	root->num = 1;
	
	root->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->num = 2;
	root->pLeft->pFather = root;
	root->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->pLeft->num = 4;\
	root->pLeft->pLeft->pFather = root->pLeft;
	root->pLeft->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->pLeft->pLeft->num = 6;
	root->pLeft->pLeft->pLeft->pFather = root->pLeft->pLeft;
	root->pLeft->pLeft->pLeft->pLeft = NULL;
	root->pLeft->pLeft->pLeft->pRight = NULL;


	root->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pLeft->pRight->num = 5;
	root->pLeft->pRight->pFather = root->pLeft;
	root->pLeft->pRight->pLeft = NULL;
	root->pLeft->pRight->pRight = NULL;

	root->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	root->pRight->num = 3;
	root->pRight->pFather = root;
	root->pRight->pLeft = NULL;
	root->pRight->pRight = NULL;

	return root;
}

//右旋
void RightSpan(BinaryTree **pTree){
	if((*pTree) == NULL)
		return;
	//两个指针 指向要改的节点和要改的节点的左孩子
	BinaryTree *pA = (*pTree);
	BinaryTree *pB = pA->pLeft;

	//先改变孩子的指向
	pA->pLeft = pB->pRight;
	pB->pRight = pA;
	//如果原先A有父亲的话 让A的父亲指向B
	if(pA->pFather != NULL){
		if(pA == pA->pFather->pLeft){
			pA->pFather->pLeft = pB;	
		}
		else{
			pA->pFather->pRight = pB;
		}
	}
	else{
		*pTree = pB;	
	}

	//再改变父亲指针的指向
	if(pA->pLeft != NULL){
		pA->pLeft->pFather = pA;
	}
	pB->pFather = pA->pFather;
	pA->pFather = pB;
	
}

//左旋
void LeftSpan(BinaryTree **pTree){
	if(*pTree == NULL) return;
	BinaryTree*	pA = *pTree;
	BinaryTree*	pB = pA->pRight;
	pA->pRight = pB->pLeft;
	pB->pLeft = pA;
	if(pA->pFather != NULL){
		if(pA == pA->pFather->pLeft){
			pA->pFather->pLeft = pB;	
		}else{
			pA->pFather->pRight = pB;	
		}
	}else{
		*pTree = pB;	
	}

	if(pA->pRight != NULL){
		pA->pRight->pFather = pA;	
	}
	pB->pFather = pA->pFather;
	pA->pFather = pB;
}
//递归前序遍历
void ProOrderTreaversal(BinaryTree *bTree){
	if(bTree == NULL) return ;
	//根
	printf("%d\t", bTree->num);
	//左
	ProOrderTreaversal(bTree->pLeft);
	//右
	ProOrderTreaversal(bTree->pRight);
	
}

//递归中序遍历
void InOrderTraversal(BinaryTree *bTree){
	if(bTree == NULL)
		return ;
	InOrderTraversal(bTree->pLeft);
	printf("%d\t", bTree->num);
	InOrderTraversal(bTree->pRight);
		
}
//递归后序遍历
void LastOrderTraversal(BinaryTree *bTree){
	if(bTree == NULL)return;
	LastOrderTraversal(bTree->pLeft);
	LastOrderTraversal(bTree->pRight);
	printf("%d\t", bTree->num);
}
	
int main(){
	
	//静态创建一棵二叉树
	BinaryTree *p = NULL;
	p = CreateTree();
	printf("前序遍历结果是：");
	ProOrderTreaversal(p);
	printf("------------------\n");
	RightSpan(&p);
	ProOrderTreaversal(p);

	printf("------------------\n");
	LeftSpan(&p);
	ProOrderTreaversal(p);
	printf("\n");
	return 0;	
}
