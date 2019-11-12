#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int *GetNext(char *pMatch){
	int *pNext = (int *)malloc(sizeof(int) * strlen(pMatch));
	pNext[0] = 0;
	int i = 1;
	int j = i - 1;
	while(i < strlen(pMatch)){
		if(pMatch[i] == pMatch[pNext[j]]){
			pNext[i] = pNext[j] + 1;
			i++;
			j = i - 1;
		}
		else if(pNext[j] == 0){
			pNext[i] = 0;
			i++;
			j = i - 1;
		}
		else{
			j = pNext[j] - 1;
		}
	}
	return pNext;
}

int KMP(char *pStr, char *pMatch){
	if(pStr == NULL || pMatch == NULL)
		return -1;
	int *pNext = NULL;
	pNext = GetNext(pMatch);

	//匹配
	int i = 0;
	int j = 0;
	while(i < strlen(pStr) && j < strlen(pMatch)){
		if(pStr[i] == pMatch[j]){
			i++;
			j++;
		}
		else{
			if(j == 0){
				i++;
			}	
			else{
				j = pNext[j - 1];	
				
			}
		}
	}
	if(j == strlen(pMatch)){
		return i - j;	
	}
	else{
		return -1;	
	}
}


int main(){
	
	int n = KMP("abcabcabcabcf", "abcf");
	printf("%d\n", n);
	return 0;	
}
