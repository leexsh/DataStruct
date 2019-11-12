#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//计数排序
void CountSort(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)
		return;
	
	//最大最小值
	int max = arr[0], min = arr[0], i;
	for(i = 0; i < nLen; i++){
		if(arr[i] > max)
			max = arr[i];
		if(arr[i] < min)
			min = arr[i];
	}
	//计数数组
	int len = max - min + 1;
	int *pMark = (int *)malloc(sizeof(int) * len);
	memset(pMark,0, sizeof(int) * len);


	for(i = 0; i < nLen; i++){
		pMark[arr[i] - min]++;
	}
	//重新排序
	int j = 0;
	for(i = 0; i < len; i++){
		while(pMark[i]){
			arr[j] = i + min;
			j++;
			pMark[i]--;
		}	
	}
	free(pMark);
	pMark = NULL;
}

int main(){
	int arr[] = {2,2,1,4,6,2,4,2,6};
	CountSort(arr, sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}
	return 0;	
}
