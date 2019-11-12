#include<stdio.h>
//插入排序
void InsertSort(int arr[], int nLen){
	int i, j, temp = 0;
	for(i = 1; i < nLen; i++){
		temp = arr[i];
		j = i - 1;
		while(temp < arr[j] && j >= 0){
			arr[j+1] = arr[j];
			j--;
		}

		arr[j+1] = temp;
	}
}


int main(){
	int arr[] = {6,9,1,2,5,4};
	InsertSort(arr, sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}
	return 0;	
}
