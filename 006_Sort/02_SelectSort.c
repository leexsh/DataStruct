#include<stdio.h>

void SelectSort(int arr[],int nLen){
	if(arr == NULL || nLen <= 0)
		return;
	int i, j,min;
	for(i = 0; i < nLen - 1; i++){
		min = i;
		for(j = i + 1; j < nLen; j++){
			if(arr[i] > arr[j]){
				min = j;
			}	
		}

		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	
}
int main(){
	int arr[] = {8,2,19,28,0,37,87,112,231};
	SelectSort(arr, sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}

	return 0;
}
