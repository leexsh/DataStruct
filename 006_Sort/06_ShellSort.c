#include<stdio.h>
void ShellSort(int arr[], int nLen){
	if(arr == NULL || nLen <= 0)
		return;
	int nGap,i,j,k,temp;
	for(nGap = nLen / 2; nGap >= 1; nGap /= 2){
		for(i = 0; i < nGap; i++){
			for(j = i + nGap; j < nLen; j += nGap){
				temp = arr[j];
				// 有序元素最后一个
				k = j - nGap;
				while(temp < arr[k] && k >= i){
					arr[k+nGap] = arr[k];
					k -= nGap;
				}
				arr[k+nGap] = temp;
			}	
		}	
	}
}


int main(){

	int arr[] = {12,4,7,16,18,1,9,10};
	ShellSort(arr, sizeof(arr)/sizeof(arr[0]));
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}

	return 0;}
