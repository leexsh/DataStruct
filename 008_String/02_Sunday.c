#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int *GetNext(char *pMatch){
	int *pNext = NULL;
	pNext = (int *)malloc(sizeof(int) * 256);
	memset(pNext, -1, sizeof(int) * 256);

	int i;
	//hash表中位置就是出现位置
	for(i = 0; i < strlen(pMatch); i++){
		pNext[pMatch[i]] = i;
	}
	return pNext;
}

int Sunday(char *pStr, char *pMatch){
	if(pStr == NULL || pMatch == NULL)
		return -1;
	int *pNext = NULL;
	pNext = GetNext(pMatch);

	int i = 0;
	int j = 0;
	int k;

	while(i < strlen(pStr) && j < strlen(pMatch))
	{
		k = i;
		
		while(pStr[i] == pMatch[j] && i < strlen(pStr) && j < strlen(pMatch))
		{
			i++;
			j++;
		}
		if(j == strlen(pMatch)){
			return i - j;
		}

		if(k + strlen(pMatch) < strlen(pStr)){
			k = k + strlen(pMatch) - pNext[pStr[k + strlen(pMatch)]];
			i = k;
			j = 0;
		}
		else{
			return -1;	
		}
	}

	
	
}

int main(){
	int n;
	n = Sunday("abcabcadfwjkldsfjlwsdfnlkpsf", "wjkldsfjl");
	printf("%d\n", n);
	return 0;
}
