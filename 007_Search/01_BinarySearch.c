#include<stdio.h>
//非递归
int BinarySearch(int arr[], int nLen, int num){
	if(arr == NULL || nLen <= 0)
		return -1;
	int low = 0;
	int high = nLen - 1;
	int mid;
	while(low <= high){
		mid = low + (high - low)/2;
		if(num == arr[mid])
			return mid;
		else if(num < arr[mid]){
			high = mid - 1;	
		}
		else if(num > arr[mid]){
			low = mid + 1;
		}
	}
	return -1;
}

int main(){
	int arr[] = {1,2,9,10,12,14,16};
	int i;
	for(i = 0; i < sizeof(arr)/ sizeof(arr[0]); i++){
		printf("%d\t", arr[i]);	
	}
	printf("\n");
	printf("输入查找的数字\n");
	int num;
	scanf("%d", &num);
	int loc = BinarySearch(arr, sizeof(arr)/sizeof(arr[0]), num);
	printf("\n位置是:%d\n",loc );
	return 0;
 }
