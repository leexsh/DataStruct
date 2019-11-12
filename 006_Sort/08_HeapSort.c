#include<stdio.h>
#include<stdlib.h>
void HeapSort(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)
		return;
	//调整
	int i,temp, j = nLen;
	while(j-- > 0){
		for(i = nLen/2 - 1; i >= 0; i--){
			//父节点的一个孩子
			if(2*i+1 <nLen && 2 * i + 2 >= nLen){
				if(arr[2*i+1] > arr[i]){
					temp = arr[i];
					arr[i] = arr[2*i+1];
					arr[2*i+1] = temp;
				}	
			}
			//父亲的两个孩子
			if(2*i +2 < nLen){
				if(arr[2*i + 1] > arr[2*i+2] && arr[2*i+1] > arr[i])
				{
					temp = arr[i];
					arr[i] = arr[2*i +1];
					arr[2*i + 1] = temp;
				}	
				else if(arr[2*i + 1] < arr[2*i +2] && arr[2*i + 2] > arr[i]){
					temp = arr[i];
					arr[i] = arr[2*i + 2];
					arr[2*i+2] = temp;
				}
			}
		}
		//拍后面
		for(i = 0; i <= nLen - 1; i++){
			temp = arr[nLen - i];
			arr[nLen-i] = arr[0];
			arr[0] = temp;
		}
	}
}

int main(){

	int arr[] = {4,10,12,1,7,18,19,6};
	int nLen = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr,sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < nLen; i++){
		printf("%d\t", arr[i]);	
	}
	printf("\n");
	return 0;
}
