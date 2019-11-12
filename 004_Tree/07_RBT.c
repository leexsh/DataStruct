#include<stdio.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0
typedef struct tree{
	int num;
	struct tree *pLeft;
	struct tree *pRight;
	struct tree *pFather;
	//颜色
	int color;
}RBT;
RBT *pRBT = NULL;

//右旋
void RightSpan(RBT **pTree){
	if((*pTree) == NULL)
		return;
	//两个指针 指向要改的节点和要改的节点的左孩子
	RBT *pA = NULL;
	pA= (*pTree);
	RBT *pB = NULL; 
	pB = pA->pLeft;

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
	//pA没有父亲 根节点成为pB
	else{

		pRBT = pB;
		//原先的
	//	*pTree = pB;	
	}

	//再改变父亲指针的指向
	if(pA->pLeft != NULL){
		pA->pLeft->pFather = pA;
	}
	pB->pFather = pA->pFather;
	pA->pFather = pB;
	
}

//左旋
void LeftSpan(RBT **pTree){
	if(*pTree == NULL) return;
	RBT* pA = NULL; 
	pA = *pTree;
	RBT* pB = NULL; 
	pB = pA->pRight;
	pA->pRight = pB->pLeft;
	pB->pLeft = pA;
	if(pA->pFather != NULL){
		if(pA == pA->pFather->pLeft){
			pA->pFather->pLeft = pB;	
		}else{
			pA->pFather->pRight = pB;	
		}
	}else{

		pRBT = pB;
		//
		//*pTree = pB;	
	}

	if(pA->pRight != NULL){
		pA->pRight->pFather = pA;	
	}
	pB->pFather = pA->pFather;
	pA->pFather= pB;
}



//发现插入节点的父亲节点
RBT *FindNode(RBT *pTree, int num){
	if(pTree == NULL)return NULL;
	while(pTree){
		if(pTree->num > num){
			if(pTree->pLeft == NULL){
				return pTree;	
			}	
			pTree = pTree->pLeft;
		}	
		else if(pTree->num < num){
			if(pTree->pRight == NULL){
				return pTree;
			}	
			pTree = pTree->pRight;
			
		}
		else{
			printf("ERROR\n");
			exit(1);
		}
	}
	
}

//获取到插入节点的叔叔节点
RBT *GetUncle(RBT *pTree){
	if(pTree == pTree->pFather->pLeft){
		return pTree->pFather->pRight;	
	}
	else{
		return pTree->pFather->pLeft;	
	}
}

//向红黑树中添加节点
void AddNode(int num){
	//插入节点的父亲节点
	RBT *pNode = NULL;
	pNode = FindNode(pRBT, num);

	//插入节点
	RBT *pTemp = NULL;
	pTemp = (RBT*)malloc(sizeof(RBT));
	pTemp->num = num;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	pTemp->pFather = pNode;
	pTemp->color = RED;

	//插入的树为空
	if(pNode == NULL){
		pRBT = pTemp;
		pRBT->color = BLACK;
		return;
	}

	//插入的树非空 先把插入节点给连上
	if(num < pNode->num){
		pNode->pLeft = pTemp;	
	}
	else{
		pNode->pRight = pTemp;	
	}
	//插入的父亲是黑色的
	if(pNode->color == BLACK){
		return;	
	}

	//变颜色

	//插入节点的叔叔指针和爷爷指针
	RBT *pUncle = NULL;
	RBT *pGrandPa = NULL;
	//其他情况
	while(pNode->color == RED){
		pGrandPa = pNode->pFather;
		pUncle = GetUncle(pNode);

		//父亲和叔叔都是红色的树
		if(pUncle != NULL && pUncle->color == RED){
			//父亲和叔叔变黑爷爷变红色
			pUncle->color = BLACK;
			pNode->color = BLACK;
			pGrandPa->color = RED;
			
			pTemp = pGrandPa;
			pNode = pTemp->pFather;
			//爷爷是根
			if(pNode == NULL){
				pGrandPa->color = BLACK;
				break;
			}
			continue;
		}

		//叔叔是黑的
		if(pUncle == NULL || pUncle->color == BLACK)
		{
			//父亲是爷爷的左
			if(pNode == pGrandPa->pLeft){
				//插入节点是父亲的右
				if(pTemp == pNode->pRight){
					pTemp = pNode;
					LeftSpan(&pTemp);
					pNode = pTemp->pFather;
					continue;
				}
				//插入节点是父亲的左
				if(pTemp == pNode->pLeft){
					pGrandPa->color = RED;
					pNode->color = BLACK;
					RightSpan(&pGrandPa);
					break;
					
				}
			}	
			
			//父亲节点是爷爷的右
			if(pNode == pGrandPa->pRight){
				//插入节点是父亲的左
				if(pTemp == pNode->pLeft){
					pTemp = pNode;
					RightSpan(&pTemp);
					pNode = pTemp->pFather;
					continue;
					
				}
			//	插入节点是父亲的右
				if(pTemp == pNode->pRight){
					pGrandPa->color = RED;
					pNode->color = BLACK;
					LeftSpan(&pGrandPa);
					break;
				}
					
			}
			
		}
	}
}

//发现删除的节点
RBT *FindNode(RBT *pTree, int num){
	if(pTree == NULL) return NULL;
	while(pTree){
		if(pTree->num == num){
			return pTree;	
		}
		else if(pTree->pLeft != NULL)
			pTree = pTree->pLeft;
		else {
			pTree = pTree->pRight;
		}
	}
	return NULL;
	
}

//在红黑树中删除节点
void DelNode(int num){
	//要删除的节点
	RBT *pTemp = NULL;
	pTemp = FindNode(pRBT, num);
	if(pTemp == NULL)
		return;
	//删除节点的父亲节点
	RBT *pNode = NULL;
	pNode = pTemp->pFather;
	//两个孩子
	RBT *pMark = NULL;
	if(pTemp->pLeft != NULL && pTemp->pRight != NULL){
		pMark = pTemp;
		pTemp = pTemp->pLeft;
		while(pTemp->pRight != NULL){
			pTemp = pTemp->pRight;
		}
		pMark->num = pTemp->num;
		free(pTemp);
		pTemp = NULL;
	}
	
	//删除的是根
	if(pNode == NULL){
		//根无左右孩子
		if(pTemp->pLeft == NULL && pTemp->pRight == NULL){
			free(pTemp);
			pTemp = NULL;
			pRBT = NULL;
			return;
		}
		//根只有一个孩子 根的孩子成为新的根
		else if(pTemp->pLeft != NULL || pTemp->pRight != NULL){
			pRBT = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			free(pTemp);
			pTemp = NULL;

			pRBT->color = BLACK;
			return;
		}		
	}
	
	//非根 红色
	if(pTemp->color == RED){
		if(pTemp == pNode->pLeft)
			pNode->pLeft = NULL;
		else
			pNode->pRight = NULL;

		free(pTemp);
		pTemp = NULL;
		return;
	}

	//删除的节点是黑色的 而且有一个红孩子
	if(pTemp->color == BLACK &&(pTemp->pLeft != NULL || pTemp->pRight != NULL)){	
		if(pTemp == pNode->pLeft){
			pNode->pLeft = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pNode->pLeft->color = BLACK;
			pNode->pLeft->pFather = pNode;
			free(pTemp);
			pTemp = NULL;
			return;
		}
		
		else{
			pNode->pRight  = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pNode->pRight->color = BLACK;
			pNode->pRight->pFather = pNode;
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}

	//获取到删除节点的兄弟节点 
	RBT *pBrother = GetUncle(pTemp);
	if(pTemp == pNode->pLeft){
		pNode->pLeft = NULL;
	}else{
		pNode->pRight = NULL;	
	}
	while(1){
		//兄弟是红色的
		if(pBrother->color == RED){
			pNode->color = RED;
			pBrother->color = BLACK;
			if(pBrother == pNode->pRight){
				LeftSpan(&pNode);
				//更新兄弟指针
				pBrother = pBrother->pLeft;
				continue;
			}
			else{
				RightSpan(&pNode);
				pBrother = pBrother->pRight;
				continue;
			}
		}

		//兄弟的颜色是黑的
		if(pBrother->color == BLACK)	
		{
			//两个侄子全黑
			if((pBrother->pLeft == NULL && pBrother->pRight == NULL)
				||((pBrother->pLeft != NULL && pBrother->pLeft->color == BLACK)&&(pBrother->pRight != NULL && pBrother->pRight->color == BLACK))){
				//父亲是红的
				if(pNode->color == RED){
					pNode->color = BLACK;
					pBrother->color = RED;
					break;
				}
				
				//父亲是黑的
				if(pNode->color == BLACK){
					pBrother->color = RED;
					pTemp = pNode;
					pNode = pNode->pFather;
					if(pNode == NULL)
						break;

					pBrother = GetUncle(pTemp);
					continue;
				}
				
			}
			//左侄子红 右侄子黑
			if((pBrother->pLeft != NULL && pBrother->pLeft->color == RED) && (pBrother->pRight == NULL || pBrother->pRight->color == BLACK))
			{
				//兄弟是父亲的右
				if(pBrother == pNode->pRight){
					pBrother->color = RED;
					pBrother->pLeft->color = BLACK;
					RightSpan(&pBrother);
					pBrother = pNode->pRight;
					continue;
					
				}

				if(pBrother == pNode->pLeft){
					pBrother->color = pNode->color;
					pNode->color = BLACK;
					pBrother->pLeft->color = BLACK;
					RightSpan(&pNode);
					break;
				}
				
			}

			//右侄子是红的
			if(pBrother->pRight != NULL && pBrother->pRight->color == RED)
			{
				if(pBrother == pNode->pLeft){
					pBrother->color = RED;
					pBrother->pRight->color = BLACK;
					LeftSpan(&pBrother);
					pBrother = pNode->pLeft;
					continue;
				}
				if(pBrother == pNode->pRight){
					pBrother->color = pNode->color;
					pNode->color = BLACK;
					pBrother->pRight->color = BLACK;
					LeftSpan(&pNode);
					break;
						
					
				}

			}
	}
}
	free(pMark);
	pMark = NULL;
}
//构造一棵红黑树

//递归前序遍历
void ProOrderTreaversal(RBT *bTree){
	if(bTree == NULL) return ;
	//根
	printf("num = %d\tcolor = %d\n", bTree->num,bTree->color);
	//左
	ProOrderTreaversal(bTree->pLeft);
	//右
	ProOrderTreaversal(bTree->pRight);
	
}

	
int main(){
	
	//静态创建一棵二叉树
	int arr[] = {11,2,14,1,7,15,5,8};
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		AddNode(arr[i])	;
		
	}
	printf("前序遍历结果是：");
	ProOrderTreaversal(pRBT);
	printf("------------------\n");
	return 0;	
}
