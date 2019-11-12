#include<stdio.h>

//初始冒泡排序
void BubbleSort(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)return;
	int i, j;
	for(i = 0; i < nLen - 1; i++){
		for(j = 0; j < nLen - i -1; j++){
			if(arr[j] > arr[j + 1]){
				arr[j] = arr[j]^arr[j+ 1];
				arr[j+1] = arr[j]^arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];
			}
		}
	}

}

//设置个标志位 如果有序就直接返回了
void BubbleSort1(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)return;
	int i, j, nFlag;
	for(i = 0; i < nLen - 1; i++){
		nFlag = 0;
		for(j = 0; j < nLen - i -1; j++){
			if(arr[j] > arr[j + 1]){
				nFlag = 1;
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
		if(nFlag == 0)
			break;
	}
}


//最终优化
void BubbleSort2(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)return;
	int i, j, nFlag, nCount = 0;
	for(i = 0; i < nLen - 1; i++){
		nFlag = 0;
		for(j = 0; j < nLen - i -1; j++){
			nCount++;
			if(arr[j] > arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				nFlag = j+1;
			}
		}
	
		i = nLen - nFlag -1;
	}
	printf("%d\n", nCount);
}
int main(){

	int arr[] = {5,4,2,7,6,1,8};
	BubbleSort2(arr, sizeof(arr) / sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}
	printf("\n");
	return 0;	
}
