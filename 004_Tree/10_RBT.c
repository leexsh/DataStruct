#include<stdio.h>
#include<stdlib.h>

enum COLOR{RED,BLACK};

typedef struct rbt
{
	int nValue;
	int nColor;
	struct rbt *pLeft;
	struct rbt *pRight;
	struct rbt *pFather;
}RBT;

RBT *pRBT = NULL;

void RightRotate(RBT **pTree)
{
	if(*pTree == NULL)return;

	RBT *pNode = NULL;
	RBT *pMark = NULL;
	pNode = *pTree;
	pMark = pNode->pLeft;

	//三个孩子关系
	pNode->pLeft = pMark->pRight;
	pMark->pRight = pNode;

	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pLeft != NULL)
	{
		pNode->pLeft->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}
void LeftRotate(RBT **pTree)
{
	if(*pTree == NULL)return;

	RBT *pNode = NULL;
	RBT *pMark = NULL;
	pNode = *pTree;
	pMark = pNode->pRight;

	//三个孩子关系
	pNode->pRight = pMark->pLeft;
	pMark->pLeft = pNode;

	if(pNode->pFather != NULL)
	{
		if(pNode == pNode->pFather->pLeft)
		{
			pNode->pFather->pLeft = pMark;
		}
		else
		{
			pNode->pFather->pRight = pMark;
		}
	}
	else
	{
		pRBT = pMark;
	}

	//三个父亲关系
	if(pNode->pRight != NULL)
	{
		pNode->pRight->pFather = pNode;
	}

	pMark->pFather = pNode->pFather;
	pNode->pFather = pMark;
}

RBT *FindNode(RBT *pTree,int nNum)
{
	if(pTree == NULL)return NULL;

	while(pTree)
	{
		if(pTree->nValue > nNum)
		{
			if(pTree->pLeft == NULL)
			{
				return pTree;
			}
			pTree = pTree->pLeft;
		}
		else if(pTree->nValue < nNum)
		{
			if(pTree->pRight == NULL)
			{
				return pTree;
			}
			pTree = pTree->pRight;
		}
		else
		{
			printf("data error.\n");
			exit(1);
		}
	}
}

RBT *GetUncle(RBT *pNode)
{
	if(pNode == pNode->pFather->pLeft)
	{
		return pNode->pFather->pRight;
	}
	else
	{
		return pNode->pFather->pLeft;
	}
}


void AddNode(int nNum)
{
	RBT *pNode = NULL;
	pNode = FindNode(pRBT, nNum);

	RBT *pTemp = NULL;
	pTemp = (RBT*)malloc(sizeof(RBT));
	pTemp->pFather = pNode;
	pTmep->num = nNum;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	pTemp->color = RED;
	
	if(pNode == NULL){
		pRBT = pTemp;
		pRBT->color = BLACK;
		return;
	}
	if(nNum < pNode->num)
		pNode->pLeft = pTemp;
	else
		pNode->pRight = pTemp;
	if(pNode->color == BLACK)
		return;
	
	RBT *pGrand = NULL;
	RBT *pUncle = NULL;
	while(pNode->color == RED){
		pGrand = pNode->pFather;
		pUncle = GetUncle(pNode);
		if(pUncle->color == RED){
			pNode->color = BLACK;
			pUncle->color = BLACK;
			pGrand->color = RED;
			
			pTemp = pGrand;
			pNode = pTemp->pFather;
			if(pNode == NULL){
				pGrand->color = BLACK;
				break;
			}
			continue;
		}

		if(pUncle== NULL || pUncle->color == BLACK){
			if(pUncle == pUncle->pFather->pRight){
				if(pTemp == pNode->pRight){
					pTemp = pNode;
					
					LeftRotate(&pTemp);
					pNode = pTemp->pFather;
					continue;
				}
				else{
					pGrand->color = RED;
					pNode->color = BLACk;
					RightRotate(&pGrand);
					break;
				}
			}
			if(pUncle == pUncle->pFather->pLeft){
				if(pTemp == pNode->pLeft){
					pTemp = pNode;
					RightRotate(&pTemp);
					pNode = pTemp->pFather;
					continue;
				}	
				else{
					pGrand->color = RED;
					pNode->color = BLACk;
					LeftRotate(&pGrand);
					return;
				
			}
		}
		
	}
}


void Traversal(RBT *pTree)
{
	if(pTree == NULL)return;

	printf("col == %d\tval == %d\n",pTree->nColor,pTree->nValue);

	Traversal(pTree->pLeft);
	Traversal(pTree->pRight);
}

RBT *Search(RBT *pTree,int nNum)
{
	if(pTree == NULL)return NULL;

	while(pTree)
	{
		if(pTree->nValue == nNum)
		{
			return pTree;
		}
		else if(pTree->nValue > nNum)
		{
			pTree = pTree->pLeft;
		}
		else
		{
			pTree = pTree->pRight;
		}
	}

	return NULL;
}

void DelNode(RBT *pTree,int nNum)
{
	RBT *pTemp = NULL;
	pTemp = Search(pTree, nNum);
	if(pTemp == NULL)
		return;
	RBT *pMark = NULL;
	if(pTemp->pLeft != NULL && pTemp->pRight != NULL){
		pMark = pTemp;
		pTemp = pTemp->pLeft;
		while(pTemp->pRight != NULL){
			pTemp = pTemp->pRight;
		}

		pMark->nNum = pTemp->nNum;
	}
	if(pTemp->pFather == NULL){
		if(pTemp->pLeft == NULL && pTemp->pRight == NULL){
			free(pTemp);
			pTemp = NULL;
			pRBT = NULL;
			return;
		}	
		if(pTemp->pLeft != NULL || pTemp->pRBT != NULL){
			pRBT = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pRBT->color = BLACK;
			pRBT->pFather = NULL;
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}
	if(pTemp->color == RED){
		if(pTemp == pTemp->pFather->pLeft){
			pTemp->pFather->pLeft = NULL;
		}	
		else
			pTemp->pFather->pRight = NULL;

		free(pTemp);
		pTemp = NULL;

	}
	if((pTemp->color == BLACk) && (pTemp->pLeft != NULL || pTemp->pRight != NULL)){
		if(pTemp == pTemp->pFather->pLeft){
			pTemp->pFather->pLeft = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pTemp->pFather->pLeft->color = BLACk;
			pTemp->pFather->pLeft->pFather = pTemp->pFather;
		}
		else{
			pTemp->pFather->pRight = pTemp->pLeft ? pTemp->pLeft : pTemp->pRight;
			pTemp->pFather->pRight->color = BLACk;
			pTemp->pFather->pRight->pFather = pTemp->pFather;
		}
		free(pTemp);
		pTemp = NULL;
		return;
	}
	//黑色 非根 且无孩子
	RBT *pNode = pTemp->pFather;
	RBT *pBrother = GetUncle(pTemp);

	pMark = pTemp;

	//假删除
	if(pTemp == pNode->pLeft)
	{
		pNode->pLeft = NULL;
	}
	else
	{
		pNode->pRight = NULL;
	}

	while(1)
	{
		//5.1兄弟是红的
		if(pBrother->nColor == RED)
		{
			pNode->nColor = RED;
			pBrother->nColor = BLACK;

			//5.1.1兄弟是父亲的右
			if(pBrother == pNode->pRight)
			{
				LeftRotate(&pNode);

				pBrother = pNode->pRight;
				continue;
			}

			//5.1.2兄弟是父亲的左
			if(pBrother == pNode->pLeft)
			{
				RightRotate(&pNode);

				pBrother = pNode->pLeft;
				continue;
			}
		}

		//5.2兄弟是黑的
		if(pBrother->nColor == BLACK)
		{
			//5.2.1两个侄子全黑
			if((pBrother->pLeft == NULL && pBrother->pRight == NULL)||(
				(pBrother->pLeft != NULL && pBrother->pLeft->nColor == BLACK)&&
				(pBrother->pRight != NULL && pBrother->pRight->nColor == BLACK)))
			{
				//5.2.1.1父亲是红色的
				if(pNode->nColor == RED)
				{
					pNode->nColor = BLACK;
					pBrother->nColor = RED;
					break;
				}

				//5.2.1.2父亲是黑色
				if(pNode->nColor == BLACK)
				{
					pBrother->nColor = RED;

					pTemp = pNode;
					pNode = pTemp->pFather;

					//根
					if(pNode == NULL)
					{
						break;
					}

					pBrother = GetUncle(pTemp);
					continue;
				}
			}

			//5.2.2左侄子红 右侄子黑
			if((pBrother->pLeft != NULL && pBrother->pLeft->nColor == RED)&&
				(pBrother->pRight == NULL || pBrother->pRight->nColor == BLACK))
			{
				//5.2.2.1兄弟是父亲的右
				if(pBrother == pNode->pRight)
				{
					pBrother->nColor = RED;
					pBrother->pLeft->nColor = BLACK;

					RightRotate(&pBrother);

					pBrother = pNode->pRight;
					continue;
				}

				//5.2.2.2兄弟是父亲的左
				if(pBrother == pNode->pLeft)
				{
					pBrother->nColor = pNode->nColor;
					pNode->nColor = BLACK;
					pBrother->pLeft->nColor = BLACK;

					RightRotate(&pNode);

					break;
				}
			}

			//5.2.3右侄子是红的
			if(pBrother->pRight != NULL && pBrother->pRight->nColor == RED)
			{
				//5.2.3.1兄弟是父亲的左
				if(pBrother == pNode->pLeft)
				{
					pBrother->nColor = RED;
					pBrother->pRight->nColor = BLACK;

					LeftRotate(&pBrother);

					pBrother = pNode->pLeft;
					continue;
				}

				//5.2.3.2兄弟是父亲的右
				if(pBrother == pNode->pRight)
				{
					pBrother->nColor = pNode->nColor;
					pNode->nColor = BLACK;
					pBrother->pRight->nColor = BLACK;

					LeftRotate(&pNode);
					break;
				}
			}
		}
	}
	free(pMark);
	pMark = NULL;
}
	
int main()
{
	int arr[] = {11,2,14,1,7,15,5,8};

	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		AddNode(arr[i]);
	}
	Traversal(pRBT);

	printf("===========================\n");
/*	AddNode(4);
	Traversal(pRBT);
*/

	DelNode(pRBT,1);
	Traversal(pRBT);
	printf("===========================\n");
	DelNode(pRBT,2);
	Traversal(pRBT);

	return 0;
}
