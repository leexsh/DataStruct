#include<stdio.h>
#include<stdlib.h>
typedef struct list{
	int num;
	struct list *pNext;
}List;

// 创建单向链表
List *CreateList(){
	List *pHead = NULL;
	List *pTail = NULL;
	int n;
	printf("请输入节点个数\n");
	scanf("%d",&n);
	List *pTemp = NULL;
	int nValue;
	while(n-- > 0){

		printf("请输入节点的值\n");
		scanf("%d",&nValue);
		pTemp = (List*)malloc(sizeof(List));
		pTemp->num = nValue;
		pTemp->pNext = NULL;
		if(pHead == NULL){
			pHead = pTemp;	
		}else{
			pTail->pNext = pTemp;	
		}
		pTail = pTemp;
	}

	return pHead;
}

//利用数组逆序打印单向链表
void RevsPrint1(List *pHead){
	int n = 0;
	while(pHead){
		List *p = pHead;
		while(p != NULL){
			n++;
			p = p->pNext;
		}
		int	arr[n];
		p = pHead;
		while(p != NULL){
			for(int i = 0; i < n; i++){
				arr[i] = p->num;
				p = p->pNext;
			}
		}
	for(int i = n-1;i>= 0;i-- ){
			printf("%d ", arr[i]);	
		if(i == 0)return;
	}
	}
}

//头插入逆序
void revsPrint2(List *pHead){
	while(pHead){
		List *newHead = (List*)malloc(sizeof(List));
		newHead->pNext = NULL;
		List *pTemp = NULL;
		while(pHead != NULL){
			pTemp = (List*)malloc(sizeof(List));
			pTemp->num = pHead->num;
			pTemp->pNext = newHead->pNext;
			newHead->pNext = pTemp;
			pHead = pHead->pNext;	
		}
		List *p = newHead->pNext;
		while(p != NULL){
			printf("%d ", p->num);
			p = p->pNext;	
		}
		
	}	
}
//递归逆序
void revsPrint3(List *pHead){
	if(pHead == NULL) return;
	else{
		revsPrint3(pHead->pNext);
	}
	printf("%d ", pHead->num);
}

//倒置一个单向链表
List *ReverseList(List *pHead){
	if(pHead == NULL || pHead->pNext == NULL)
		return pHead;
	List *p1 = NULL;//被指向
	List *p2 = pHead;//指向
	List *p3 = pHead->pNext;//断开的位置
	while(p3 != NULL){
		p2->pNext = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->pNext;
	}
		
	p2->pNext = p1;
	return p2;
}	
//链表的头添加
List *HeadAdd(List *pHead){
	printf("请输入要添加的节点的值：\n");
	int n;
	scanf("%d", &n);
	List *pNode = (List *)malloc(sizeof(List));
	pNode->num = n;
	pNode->pNext = pHead;
	return pNode;
}
//链表的头删除
List *HeadDel(List *pHead){
	List *pNode = (List*)malloc(sizeof(List));
	pNode->pNext = pHead;
	pNode->pNext = pNode->pNext->pNext;
	free(pHead);
	pHead = NULL;
	return pNode->pNext;
}

void Printf(List *pHead){

	while(pHead){
		printf("%d ", pHead->num);
		pHead = pHead->pNext;
	}
}

int main(){

	List *pHead = NULL;
	pHead = CreateList();
	printf("链表中的数据是：\n");
	Printf(pHead);
	printf("\n-----1.数组逆序方法----\n");
	RevsPrint1(pHead);
	printf("\n-----2.链表逆序方法----\n");
	revsPrint2(pHead);
	printf("\n-----3.递归逆序方法----\n");
	revsPrint3(pHead);
	printf("\n-----4.倒置链表----\n");
	pHead = ReverseList(pHead);
	Printf(pHead);
	printf("\n");
	printf("链表的头添加\n");
	pHead = HeadAdd(pHead);
	Printf(pHead);
	printf("\n链表的头删除\n");
	pHead = HeadDel(pHead);
	Printf(pHead);
	printf("\n");
	

	return 0;
}
