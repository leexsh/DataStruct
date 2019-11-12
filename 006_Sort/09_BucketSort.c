#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct bucket{
	int num;
	struct bucket *pNext;
	struct bucket *pPre;
}Bucket;
void Sort(Bucket *p){
	if(p == NULL || p->pNext == NULL)
		return;
	Bucket *pUnSort = NULL;
	Bucket *pSort = NULL;
	int temp;
	pUnSort = p->pNext;
	while(pUnSort){
		pSort = pUnSort->pPre;
		temp = pUnSort->num;
		while(pSort != NULL && pSort->num > temp){
			pSort->pNext->num = pSort->num;
			pSort = pSort->pPre;
		}
		if(pSort == NULL)
			p->num = temp;
		else{
			pSort->pNext->num = temp;
			}

		pUnSort = pUnSort->pNext;
	}

}

//桶排序
void BucketSort(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)
		return;

	int nMax = arr[0],nMin = arr[0];
	
	int i;
	// 找最大值和最小值
	for(i = 1; i < nLen; i++){
		if(arr[i] > nMax)
			nMax = arr[i];
		if(arr[i] < nMin)
			nMin = arr[i];
	}

	int beishu = 1, nNum = nMin;
	//数字位数
	while(nNum > 10){
		nNum /= 10;
		beishu *= 10;
	}
	

	int nMinIndex = nMin / beishu;
	int nMaxIndex = nMax / beishu;
	int nGap = (nMaxIndex - nMinIndex) + 1;

	Bucket **pMark = (Bucket**)malloc(sizeof(Bucket*)*nGap);
	memset(pMark, 0, sizeof(Bucket*)*nGap);
	
	Bucket *pTemp = NULL;
	int nIndex;
	// 将数据插入到桶中
	for(i = 0; i < nLen; i++){
		nIndex = arr[i]/beishu - nMinIndex;

		pTemp = (Bucket*)malloc(sizeof(Bucket));
		pTemp->num = arr[i];
		pTemp->pNext = NULL;
		pTemp->pPre = NULL;
		pTemp->pNext = pMark[nIndex];
		if(pMark[nIndex] != NULL){
			pMark[nIndex]->pPre = pTemp;	
		}
		pMark[nIndex] = pTemp;
	}
	for(i = 0; i < nGap; i++){
		Sort(pMark[i]);
	}

	//拷贝回原数组  并使放空间
	int j = 0;
	for(i = 0; i < nGap; i++){
		pTemp = pMark[i];
		while(pTemp){
			arr[j] = pTemp->num;
			pTemp = pTemp->pNext;
			j++;
		}
	}
	

	//释放空间
	for(i = 0; i < nGap; i++){
		Bucket *pDel = NULL;
		pTemp = pMark[i];
		while(pTemp){
			pDel = pTemp;
			pTemp = pTemp->pNext;
			free(pDel);
			pDel = NULL;
		}	
	}
	free(pMark);
	pMark = NULL;


}

int main(){
	int arr[] = {123,456,111,234,797,345,678.909};
	BucketSort(arr, sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("%d\t", arr[i])	;
	}
	return 0;	
}
