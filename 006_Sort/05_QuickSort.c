#include<stdio.h>
//快速排序-挖坑填补法
int sort1(int arr[], int nLow, int nHigh){
	int temp;
	temp = arr[nLow];
	while(nLow < nHigh){
		while(nHigh > nLow){
			if(arr[nHigh] < temp){
				arr[nLow] = arr[nHigh];
				nLow++;
				break;
			}	
			nHigh--;
		}	
		while(nHigh > nLow){
			if(arr[nLow] > temp){
				arr[nHigh] = arr[nLow];
				nHigh--;
				break;
			}	
			nLow++;
		}
	}
	arr[nLow] = temp;
	return nLow;
}
void QuickSort1(int arr[], int nLow, int nHigh){
	if(arr == NULL || nHigh <= nLow)
		return;
	int nStandard;
	nStandard = sort1(arr, nLow, nHigh);
	QuickSort1(arr, nLow, nStandard-1);
	QuickSort1(arr, nStandard + 1, nHigh);
}

//快速排序-利用区间分割
int sort2(int arr[], int nLow, int nHigh){
	int nQu = nLow - 1;
//	for(nLow; nLow < nHigh; nLow++){
//		if(arr[nLow] < arr[nHigh]){
//			if(++nQu != nLow){
//				arr[nQu] = arr[nQu]^arr[nLow];
//				arr[nLow] = arr[nQu]^arr[nLow];
//				arr[nQu] = arr[nQu]^arr[nLow];
//			}	
//		}	
//	}
	while(nLow != nHigh){
		if(arr[nLow] < arr[nHigh]){
			int x = arr[nLow];
			arr[nLow] = arr[++nQu];
			arr[nQu] = x;
		}
		nLow++;
	}

	int x = arr[nHigh];
	arr[nHigh] = arr[++nQu];
	arr[nQu] = x;
	//if(++nQu != nHigh){
	//	arr[nQu] = arr[nQu]^arr[nHigh];
	//	arr[nHigh] = arr[nQu]^arr[nHigh];
	//	arr[nQu] = arr[nQu]^arr[nHigh];
		
//	}
	return nQu;
}
void QuickSort2(int arr[],int nLow, int nHigh){
	if(arr == NULL || nHigh <= nLow)
		return;
	int nStandard;
	nStandard = sort2(arr, nLow, nHigh);
	QuickSort2(arr, nLow, nStandard - 1);
	QuickSort2(arr, nStandard + 1, nHigh);
}
int main(){

	int arr[] = {12,4,7,16,18,1,9,10};
	int nLen = sizeof(arr) / sizeof(arr[0]);
	QuickSort1(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);
	int i;
	for(i = 0; i < nLen; i++){
		printf("%d\t", arr[i]);	
	}
	printf("\n");
	return 0;
}
