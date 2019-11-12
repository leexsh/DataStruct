#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct hash{
	//节点值
	int nValue;
	struct hash *pNext;
	//下标
	int nIndex;
}Hash;

Hash **CreateHashTable(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)
		return NULL;
	Hash **pHash = NULL;
	pHash = (Hash **)malloc(sizeof(Hash*) * nLen);
	memset(pHash, 0, sizeof(Hash*) * nLen);
	int i, nIndex;
	Hash *pTemp = NULL;
	for(i = 0; i < nLen; i++){
		
		nIndex = arr[i] % nLen;

		pTemp = (Hash*)malloc(sizeof(Hash));
		pTemp->nValue = arr[i];
		pTemp->nIndex = i;
		//头插法
		pTemp->pNext = pHash[nIndex];
		pHash[nIndex] = pTemp;
	}

	return pHash;
}

int Search(Hash **pHash, int nLen, int num){
	if(pHash == NULL || nLen <0 ){
		return -1;
	}	
	int nIndex;
	nIndex = num % nLen;
	Hash *pNode = pHash[nIndex];
	while(pNode){
		if(pNode->nValue == num){
			return pNode->nIndex;	
		}	
		pNode = pNode->pNext;

	}

	return -1;
}


int main(){
	int arr[] = {10,3674,78,29, 880,6,8,1,227,32,199};
	Hash **pHash;
	pHash = CreateHashTable(arr, sizeof(arr)/sizeof(arr[0]));
	int n;
	n = Search(pHash, sizeof(arr)/sizeof(arr[0]), 3674);
	printf("%d\n",n );

	return 0;
}
