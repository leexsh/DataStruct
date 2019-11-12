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
//动态创建一棵二叉树
void DynamicCreateTree(BinaryTree **pTree){
	int num;
	printf("请输入二叉树节点的值\n");
	scanf("%d", &num);
	if(num == 0){
		return;	
	}
	//申请节点
	(*pTree) = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pTree)->num = num;
	(*pTree)->pLeft = NULL;
	(*pTree)->pRight = NULL;

	//左子树
	DynamicCreateTree(&((*pTree)->pLeft));
	//右子树
	DynamicCreateTree(&((*pTree)->pRight));
}

//利用结构体数组来构建完全二叉树
//arr数组首地址 n数组长度
BinaryTree *CreateWanTree(int arr[],int n){
	if(n <= 0 || arr == NULL) return NULL;
	//申请结构体数组
	BinaryTree *TreeArr;
	TreeArr = (BinaryTree*)malloc(sizeof(BinaryTree)* n);

	//赋值
	int i;
	for(i = 0; i < n; i++){
		TreeArr[i].num = arr[i];
		TreeArr[i].pLeft = NULL;
		TreeArr[i].pRight = NULL;
	}
	//左右关联
	for(i = 0; i <= n/2 - 1; i++){
		if(2 * i + 1 <= n - 1){
			TreeArr[i].pLeft = &TreeArr[2 * i + 1];	
		}
		if(2* i +2 <= n - 1){
			TreeArr[i].pRight = &TreeArr[2*i + 2];
		}
	}

	return TreeArr;

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
	OrderTraversal(bTree->pRight);
		
}
//递归后序遍历
void LastOrderTraversal(BinaryTree *bTree){
	if(bTree == NULL)return;
	LastOrderTraversal(bTree->pLeft);
	LastOrderTraversal(bTree->pRight);
	printf("%d\t", bTree->num);
}
	
//初始化
void Q_Init(Queue **pQueue){
	(*pQueue) = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
	(*pQueue)->nSize  = 0;
}
int main(){
	
	//静态创建一棵二叉树
	BinaryTree *p = NULL;
	p = CreateTree();
	printf("前序遍历结果是：");
	ProOrderTreaversal(p);
	printf("\n中序遍历结果是：");
	InOrderTraversal(p);
	printf("\n后序遍历结果是：");
	LastOrderTraversal(p);
	printf("\n");
	printf("------------------\n");
	
	//动态创建二叉树 1 2 4 0 0 5 0 0 3 6 0 0 0
	BinaryTree *p1 = NULL;
	DynamicCreateTree(&p1);
	printf("前序遍历结果是：");
	ProOrderTreaversal(p1);
	printf("\n中序遍历结果是：");
	InOrderTraversal(p1);
	printf("\n后序遍历结果是：");
	LastOrderTraversal(p1);
	printf("\n");
	printf("------------------\n");
	
	//数组创建完全二叉树
	int arr[] = {1,2,3,4,5,6};
	BinaryTree *p2 = CreateWanTree(arr,6);
	printf("前序遍历结果是：");
	ProOrderTreaversal(p2);
	printf("\n中序遍历结果是：");
	InOrderTraversal(p2);
	printf("\n后序遍历结果是：");
	LastOrderTraversal(p2);
	printf("\n");
	return 0;	
}
