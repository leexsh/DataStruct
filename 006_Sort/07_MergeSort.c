#include<stdio.h>
#include<stdlib.h>
void Sort(int arr[], int nLow, int nHigh){
	int begin1, end1, begin2, end2;
	begin1 = nLow;
	end1 = nLow + (nHigh - nLow)/2;
	begin2 = end1 + 1;
	end2 = nHigh;
	int *pMark = NULL;
	pMark = (int *)malloc(sizeof(int)*(nHigh - nLow +1));
	int i = 0;
	//分组
	while(begin1 <= end1 && begin2  <= end2){
		if(arr[begin1] < arr[begin2]){
			pMark[i++] = arr[begin1++];
		}
		if(arr[begin1] > arr[begin2]){
			pMark[i++] = arr[begin2++];	
		}
	}

	while(begin1 <= end1){
		pMark[i++] = arr[begin1++];
	}

	while(begin2 <= end2){
		pMark[i++] = arr[begin2++];	
	}
	//放回原数组 
	for(i = 0; i < nHigh - nLow + 1; i++){
		arr[nLow + i] = pMark[i];	
	}
	free(pMark);
	pMark = NULL;

}
void MergeSort(int arr[], int nLow, int nHigh){
	if(nLow >= nHigh || arr == NULL)
		return;
	int nMid;
	//归并
	nMid = nLow + (nHigh - nLow) / 2;
	MergeSort(arr, nLow, nMid);
	MergeSort(arr, nMid + 1, nHigh);

	//排序
	Sort(arr, nLow, nHigh);

}
int main(){

	int arr[] = {12,4,7,16,18,1,9,10};
	int nLen = sizeof(arr) / sizeof(arr[0]);
	MergeSort(arr,0, sizeof(arr)/sizeof(arr[0]) - 1);
	int i;
	for(i = 0; i < nLen; i++){
		printf("%d\t", arr[i]);	
	}
	printf("\n");
	return 0;
}
